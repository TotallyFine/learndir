### 特点
目标检测的四个基本步骤（候选区域生成，特征提取，分类，位置精修）被统一到一个深度网络框架中。所有的计算没有重复，完全在GPU中完成，提高运行速度

### 三个主要问题
1 如何设计区域生成网络
2 如何训练区域生成网络
3 如何让区域生成网络和fast rcnn（提取特征、分类、位置精修）共享特征提取网络

### 区域生成网络的结构
基本设想：在提取好的特征图上，对所有可能的候选框进行判别。由于后续还有位置精修，所以候选框实际比较稀疏

论文中的输入是 1 * 3 * 244 * 244,在经过一系列的卷积等操作之后得到feature 51 * 39 * 256,然后在这个feature map上进行滑动得到不同的anchor对应的原图中的区域有

### RPN核心思想
RPN的核心思想是使用CNN卷积神经网络直接产生Region Proposal，使用的方法本质上滑动窗口（在最后的卷积层上，也就是得到的feature map上），因为anchor机制和边框回归可以得到多尺度、多长宽比的Region Proposal
RPN网络也是全卷积网络，可以针对生成检测建议框的任务端到端的训练，能够同时预测出object的边界和分数。只是在CNN上额外增加了2个卷积层（全卷积cls、和reg）
1 将每个特征图的位置编码成一个特征向量在VGG中是512d,这里的每一个特征图就是一个换窗也就是一个卷积核对应的区域，使用四维的卷积核，将每一次卷积之后得到的不止是一个数字而是一个521d的向量
2 对每一个位置输出一个objectness score和regressedbounds for k个region proposal，即在每个卷积映射位置输出这个位置上多种尺度（在论文里的图片是600×1000,所以论文里设计了3种尺度，128×128, 256×256, 512×512）和长宽比（3种）的k个（33 * 3=9个）区域建议的物体得分和回归边界

如果使用VGG则RPN可以表示为VGG16+RPN

### RPN中的loss和Faster RCNN最终的loss的区别
如果使用VGG得到一个feature map，再进行分类cls、回归reg，被筛选过的框变成了ROI（Region Of Interest），进行ROI Polling和全连接之后又计算BBox的回归和分类。

Input Image经过CNN特征提取，首先来到Region Proposal网络，并有Region Proposal网络进行输出Classfication，但是这并不是在判定物体在数据集上对应的哪几类，而是输出一个Binary的值p，可以理解为0<= p <= 1，然后人工设定一个threshold=0.5,这样就筛选掉了一部分的框，而剩下的那些框被称为候选区域，也就是ROI

RPN做的事情就是，如果一个Region的p>0.5,则认为这个Region中可能是自己需要的那些类别中的某一类，但是是哪一类还不清楚，到此为止，网络只需要把所有这些可能含有物体的区域选取出来就可以了，同时RPN也会在feature map上框定这些POI感兴趣区域的大致位置，即输出Bounding Box

到此为止网络已经输出了所有需要预测的类的区域的信息，其他的Region可以不考虑，也就是不用输入到后续网络

那么接下来，假设输入RPN网络的feture map大小为64 × 64 ，那么我门提取的POI尺寸一定小于64 × 64,因为原始图像某一块物体在feature map上也以同样的比例存在。我们只需要把这些Region从feature map上扣出来，由于每个Region的尺寸可能不太一样，因为原始图像上物体大小不一样，所以我们需要将这些扣出来的Region想办法resize到和原始物体对应的相同尺寸，这一步的办法很多，可以使用Pooling或者Interpolation，一般采用Pooling，因为反向传播的时候方便

假设这些扣出来的ROI Region被我们resize到了14 × 14或者 7 × 7，那么接下来将这些Region输入普通的分类网络，最后的全连接层，就可以得到整个网络的最终输出classification，这里的分类才对应自己希望分的哪几类
同时，由于之前的RPN确定的box\region坐标比较粗略，只是大概框出了感兴趣的区域，所以这里我们再来一次精确的微调，根据每个box中的具体内容微微调整一下这个box的坐标


### 为什么在中间进行一次筛选？
如果希望分的类有有很多，不进行Region Proposal的话，最后的classification是对所有anchor狂顶的Region进行识别分类，会严重拖累网络的分类性能，难以收敛。

大量无用的Region如果都进入分类网络，而分类网络又几层卷积层和最后一层全连接层组成，参数很多，消耗计算时间。

由于Anchor对应原图中的位置和大小是固定了的，所以RPN中就是在保留一些感兴趣的Anchor，而最后对框的Regression是在初始Anchor对应的框的基础上做偏移修正和缩放，输出的是偏移量，而不是又输出一个原图上的绝对坐标！

在VGG得到的feature map上进行的滑动并不是真的滑动，而是一次卷积操作。而且所谓的Anchor并不存在于这个图中，Anchor是在原图上，如果feature map是H * W * 256,那么原图就有H * W 个Anchor

### RPN的平移不变性
在计算机视觉中的一个挑战就是平移不变性，比如人脸识别中任务中小的人脸（24×24分辨率）、大的人脸（1080×720分练率）如何能够在同一个训练好权值的网络中都能正确识别。如果图像平移了，那么Proposal出的Region也应该平移
传统主要有两种方式：
1 对图像或者feature map层进行尺度\宽高的采样
2 对使用不同尺度的滤波器（卷积核）来进采样
RPN的解决方法：
通过卷积核中心得到Proposal Region的Anchor，然后直接在原图上得到不同尺度的采样

### 窗口分类和位置精修
前面的CNN得到的512dfeature分别送入RPN中的分类层cls和窗口回归层reg
RPN的分类层(cls_score)输出每一个位置上，9个Anchor属于前景（希望分的那些类）和背景（要忽略的那些类）的概率
窗口回归层(bbox_pred)输出每一个位置上，9个Anchor对应窗口应该平移缩放的参数(x, y, w, h)
到这里并没有显示地提取候选窗口，完全使用网络自身玩车个判断和修正

### RPN如何训练
标签分类规定
为了训练RPN，需要给每个anchor分类的类标签{目标、非目标}。对于positive label，论文中给了如下规定(满足如下规定就可以判为正标签)：
1 与Ground Truth框最高IOU重叠的Anchor(也许不到0.7)
2 与任意Ground Truth框IOU大于0.7的Anchor

一个Ground Thruth可能对应多个Anchor，这样一个Ground Thruth框就有可能有多个正标签
负标签：与所有GT框IOU都限于0.3的Anchor
对于即不是正标签也不是负标签的Anchor，以及跨越图像边界的Anchor予以舍弃，因为这些对于训练没有用处

多任务损失（来自Fast RCNN）
Fast RCNN网络先得到原图上的Region，然后通过CNN得到4096d的feature，再通过两个同级输出层（cls_score层和bbox_prdict层），都是全连接层，称为multi-task

图见blog.csdn.net/lk123400/article/details/54343550

1 clsscore层，用于分类，输出k+1维数组p，表示k类和背景的概率。对每一个RoI(Region of Interesting也就是通过Selective Search得到的Region)输出概率
P = (P0, P1, P2, ..., Pk)，一般使用softmax得到

2 bbox_prdict层，用于调整候选区域位置，输出bounding box回归的位移，输出4×k维数组t，表示分别属于k类时应该平移缩放的参数
t = (tx, ty, tw, th)
tx,ty是相对于原来object proposal尺度 不变的平移，tw,th是在对数空间中相对与object proposal的高与宽

损失函数
loss_cls层评估分类损失函数。由真实分类u对应的概率决定：
L(p, u) = -logPu Pu是对于这个Anchor中真正的类预测出来的概率，以10为底

loss_bbox评估检测框定位的损失函数。比较真实分类对应的预测平移缩放参数
预测出来的是t = (tx, ty, tw, th)，真实平移缩放参数为v=(vx, vy, vw, vh)
使用smoothL1损失函数 smoothL1(x) = 0.5*x*x (|x|<1) or |x|-0.5
画一下smoothL1的损失函数 曲线，可以看到这样是为了让loss对于离群点更加鲁棒，不至于有一个稍微大的离群点就会导致loss特别大

最后的总损失，综合一下L(p, u, t, v)=L(p, u)+lambd*smoothL1(x) 当这个u是前景
L(p ,u)当这个u是背景*(这个时候就只分类而没有必要进行框的回归了)，在论文里lambd=1


### Faster R-CNN损失函数

 


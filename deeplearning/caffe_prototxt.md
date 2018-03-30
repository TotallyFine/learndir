## caffe 配置文件.prototxt

### 输入层
数据层即输入层，在caffe中数据以blob的格式进行存储和传输，这一层实现其他格式的数据和blob格式的数据进行转换，例如从imdb或者level-db转换为blob，也可以从低效的数据格式如hdf5或者图片。另外的数据的预处理也在本层实现，如减去均值，放大缩小，裁剪和镜像等。用Lenet_train_test.prototxt.txt为例。
```.prototxt
name:"LeNet"
layer {
  name: "mnist"
  type: "Data"
  top: "data"
  top: "label"
  include {
    phase: TRAIN
  }
  transform_param {
    scale: 0.00390625
  }
  data_param {
    source: "examples/mnist/mnist_train_lmdb"
    batch_size: 64
    backend: LMDB 
  }
}
```

**name:**

自己取的名字

**type:** 

层的类型。如果是Data，表示数据来源于LevelDB或LMDB。还有MemoryData 那么下面的data_param 就变成了 menory_data_param{...}

ImageData,图片格式，source是一个txt文件，每一行是一个图片的路径和标签。

WindowData，来源于windows

**top**

本层的输出，例子表明有两个输出，data和label是分类问题必须的

**bottom**

本层的输入

**include**

在其中规定是训练还是测试的层，如果没有表明那么测试和训练都有这个层

**transform_param**

数据预处理，scale表明从0-255到[0, 1),还可以添加mirror: 1/0 1表示开启，0表示关闭。mean_file_size: xxx.mean.binaryproto 后面的文件用于去均值处理。crop_size等

### 视觉层

(1) 层类型 Convolution，如LeNet的第一个卷积层
```.prototxt
layer{
  name: "conv1"
  type: "Convolution"
  bottom: "data"
  top: "conv1"
  param {
    lr_mult: 1
  }
  param {
    lr_mlt: 2
  }
  convolution_param {
    num_output: 20
    kernel_size: 5
    stride: 1
    weight_filler {
      type: "xavier"
    }
    bias_filler {
      type: "constant"
    }
  }
}
```
**lr_mult**

第一个表示权重w的学习率的系数，学习率=base_lr(定义在solver.prototxt中)，第二个是偏重bias的学习率系数

**num_output**

卷积核kernel的个数

**kernel_size**

如果卷积核的长和宽不相等，需要用kernel_h 和 kernel_w来设定。顺便一提caffe不支持3d，如果要进行3d卷积还需要进行额外的设置。

**stride**

卷积运算的步长，默认为1.也可以用stride_h 和 stride_w 来设置。

**pad**

填充边缘的大小

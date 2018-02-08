### 对什么进行初始化
  -  定义一层网络实际上就是定义Y = Wx(Y W x都是矩阵或向量)中的W，所以就是在定义参数，如果是卷积则是附带定义了对矩阵Y中的哪些元素进行运算，当然定一个激活函数或者dropout层等是对输入进行操作。

### 初始化方法
 - torch.nn.init.uniform(tensor, a=0, b=1)，均匀初始化，参数为左端点和右端点
 - torch.nn.init.normal(tensor, mean=0, std=1),正态初始化，参数为均值和方差
 - torch.nn.init.constant(tensor, val)
 - torch.nn.init.xavier_uniform(tensor, gain=1)

### 初始化方法可以直接作用于神经网络参数
 - import torch.nn as nn
 - import torch.nn.init as init
 - 
 - conv1 = nn.Con2d(3, 64, kernel_size=7, stride=2, padding=3)
 - init.xavier_uniform(con1.weight) #参数
 - init.constant(conv1.bias, 0.1) #偏差
 -
 - 对整个网络进行初始化
 - def weight_init(m):
 -     if isinatance(m, nn.Conv2d):
 -         xavier(m.weight.data)
 -         xavier(m.bias.data)

### 什么时候初始化
 - 在实例化一个网络的时候进行初始化，所以代码写在网络类的__init__()中


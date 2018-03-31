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

**weight_filter**

权重的初始化，若设置为constant，则默认为0.也可使用"xavier"或"gaussian"

**bias_filter**

偏置项的初始化，与weight filter相似

**bias_term**

是否开启偏置项

**group**

分组，默认为1组。如果大于1，则将限制卷积的连接操作在一个子集内，如果根据图像的通道来进行分组，那么第i个输出分组只能与第i个输入分组进行连接

(2) 层类型 pooling
```.prototxt
layer{
  name: "pool1"
  type: "Pooling"
  bottom: "conv1"
  top: "pool1"
  pooling_param {
    pool: MAX
    kernel_size: 2
    stride: 2
  }
}
```

(3) 激活层
```.prototxt
layer{
  name: "relu1"
  type: "ReLU"
  bottom: "ip1"
  top: "ip1"
}
```

(4) 全连接层
```.protoxtxt
layer{
  name: "ip2"
  type: "InnerProduct"
  bottom: "ip1"
  top: "ip2"
  param {
    lr_mult: 1
  }
  param {
    lr_mult: 2
  }
  inner_product_param {
    num_output: 10
    weight_filler {
      type: "xavier"
    }
    bias_filler {
      type: "constant"
    }
  }
}
```

(5) accuracy 只有测试阶段才有
```.prototxt
layer {
  name: "accuracy"
  type: "Accuracy"
  bottom: "ip2"
  bottom: "label"
  top: "accuracy"
  include {
    phase: TEST
  }
}
```

(6) Reshape层 改变形状
```.prorotxt
layer {
  name: "reshape"
  type: "Reshape"
  bottom: "input"
  top: "output"
  reshape_param {
    shape {
      dim: 0 # 表示维度不变，即输入和输出是相同的维度
      dim: 2 # 将原来的维度变为2
      dim: 3 # 将原来的维度变为3
      dim: -1 # infer it from the other dimension
    }
  }
}
```

blob是一个四维的数组n, c, w, h

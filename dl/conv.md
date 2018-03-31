### 卷积

在pytorch中实例化一层卷积网络Conv2d的时候只需要输入输出的channel即可，实例化之后的一层Conv2d会产生out_channel个卷积核，而每个卷积核的大小为(in_channel, kernel_size, kernel_size),最后的图片输出是根据输入的图片大小：(in_H-(kernel_size)+ 2 * padding) / stride + 1得到的

进行一层的卷积后输出多层feature map，feature map的数量就是就是输出的channel数。这些feature map有什么不同呢，不同的feature map是由不同的卷积核得到的，一般来说不同的卷积核学习到的特征是不同的，如果一张图中有这个卷积核所学习到的特征那么这个卷积核就相当于会被激活，就相当于输出一些比较大的值。

关于feature，还有deep feature和bottle feature的说法，bottle feature是经过多层的卷积输出小于输入
deep feature泛指经过深层次卷积之后的feature

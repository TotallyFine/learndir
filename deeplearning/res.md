### 残差块
残差块有多种不同的形式，ResNet论文里用的就是
X = ReLU(BatchNorm(Conv(Xi)))
X = ReLU(BatchNorm(Conv(X)))
Xi+1 = Xi + X

然而残差块也有多种不同的变体，ReLU、BatchNorm、Conv的位置不同就会导致多种的结构

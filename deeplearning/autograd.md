## 自动求导机制的阅读笔记

### 在进行反向传播的时候不包括子图

#### requires_grad

 - 如果输入中有一部分需要进行反向传播，那么输出的Variable的requires_grad属性也是True
 - 每一个Variable都有两个flag：requires_grad volatile
 - 反向传播从不在子图（不是主要的数据流，比如网络中的参数）中进行，所有参数一般都不能进行反向传播
 - 当需要冻结一些网络的时候可以使其不能进行反向传播，比如在finetune一个预训练的模型的时候可以将前面的部分都设置成不能进行反向传播，最后的全连接层和输出层设置成可以进行反向传播，那么在训练的时候只有最后的自己新加入的层可以得到训练。
 - 并且不需要反向传播也就意味着中间的计算结果不需要保存。
 - model = torchvision.models.resnet18(pretrained=True)
 - for param in model.parameters():
 -     param.requires_grad = False
 - # 重置最后的全连接层.新的网络的参数默认的情况下是需要进行反向传播的
 - model.fc = nn.Linear(512, 100)
 - optimizer = optim.SGD(model.fc.parameters(), lr=1e-2, momentum=0.9)

#### volatile
 - 表示不变的
 - volatile是会随着网络进行传播的，如果输入中有一部分是volatile的那么最后的输出也是volatile
 - 不会保存中间的计算结果

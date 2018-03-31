### IOU定义
物体检测需要定位出物体的bounding box，并且识别出bounding box中的物体的类别
对于bounding box的精度有一个很重要的概念，因为自己的算法不可能百分之百和人工标注的数据完全匹配。所以存在一个精度匹配的评价公式 IOU

IOU定义了两个bounding box的重叠度
设 Sa是物体A的bounding box，Sb是物体B的bounding box， Si是两者之间的重叠的部分
IOU = Si / (Sa + Sb - Si)
交集比并集

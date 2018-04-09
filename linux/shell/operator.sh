# shell基本运算符
# 算数运算符
# 关系运算符
# 布尔运算符
# 字符串运算符
# 文件测试运算符

# 原声的bash不支持简单的数学运算，但是可以通过其他命令来实现，例如awk和expr，expr最常用
# 2 + 2 之间要有空格，整个表达式要被``包围
val=`expr 2 + 2`
echo $val
# expr还执行+ - * / = %, *之前要加上\才能实现乘法运算 
echo `expr 4 \* 2` 

# == 与 !=
a=10
b=20
if [ $a == $b ]
then
    echo "a 等于 b"
fi

if [ $a != $b ]; then
    echo "a 不等于 b"
fi

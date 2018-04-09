#!/bin/bash

# shell 变量
# 定义变量时，变量名不加$，但是使用的时候加$
your_name="kx"
# 变量名和等号之间不能有任何空格
# 变量名遵守以下规则
# 1 命名只能使用英文字母，数字和下划线，首个字符不能是数字
# 2 中间不能有空格
# 3 不能使用标点符号

# 除了显示直接赋值，也可以用语句给变量赋值
# 有时shell并不会准确报错，而是在末尾进行报错

# 使用变量
echo $your_name
# 花括号不是必须的，是为了帮助编译器识别变量名的边界
# 如果拼写错误，向下面的一样，则不会有任何显示
echo ${yout_name}

# 重新赋值时不使用$
your_name='kkk'

# 使用readonly命令可以将变量定义为只读变量，只读变量的值不能改变
myUrl='http://www.baidu.com'
readonly myUrl
# 下面的语句会导致报错
# myUrl='about:blank'

# 删除变量,删除变量之后不能再次使用，unset不能删除只读变量
#unset myUrl # 会提示无法删除变量
echo $myUrl # 仍然会打印myUrl的值

# 变量类型
# 局部变量，局部变量在脚本或者命令中定义，仅在当前shell实例中有效，其他shell启动的程序不能访问局部变量
# 环境变量，所有程序包括shell启动的程序，都能访问换将变量，有些程序需要环境变量来保证其能正常运行。必要的时候，shell脚本也可以定义环境变量
# shell 变量，shell是由shell程序设置的特殊变量，shell变量中有一部分是环境变量，有一部分是局部变量，这些变量保证了shell的正常运行

# Shell字符串
# shell编程中一般用的最多的是数字和字符串。
# 字符串可以使用单引号，双引号或者不含引号

# 单引号
str='this is a string'
# 单引号中的任何字符都会原样输出，单引号中的变量是无效的，单引号字符串中不能出现单引号(对单引号转义之后也不行)
# 双引号
str="Hello, I know your name is \"$your_name\"! \n"
echo $str

# 拼接字符串
greeting="hello, "$your_name" !"
greeting_1="hello, ${your_name} !"
echo $greeting $greeting_1

# 获取字符串长度
string="abcd"
echo ${#string} # 输出4

# 提取子串
string="uestc is a school"
echo ${string:1:4} # 输出estc

# 查找子串，查找ch的位置
# 下语句输出5
echo `expr index "$string" c`

# shell数组
# bash只支持一维数组，并且没有限定数组的大小，数组元素下标从0开始，获取数组中的元素要利用下标，下标可以是整数或者算数表达式，其值应该大于等于0,同样数组名代表数组的第一个元素，打印数组名就是在打印数组第一个元素
# 定义数组,数组元素用空格分开
array=(0 1 2 3)
arr=(
0
1
2
3
)
echo $arr

# 可以单独定义数组的各个分量，可以不使用连续的下标，且下标的范围没有限制
array[6]=5
# 读取数组的一般格式
echo ${array[6]}
# 使用@符号可以获取数组中的所有元素
echo ${array[@]}

# 获取数组的长度
echo ${#array[@]}
echo ${#array[*]}
# 获取某个元素的长度
echo ${#array[n]}

# 数组的值也可以写入变量
A=1
array[7]=$A
# 下面语句打印1
echo "array 的第8个元素是 ${array[7]}"

# shell注释
# shell中没有多行注释，只能每一行加一个#号
# 在开发过程中，如果需要大段的注释，可以用{}括起来定义成函数，没有地方调用这个函数，这段代码不会执行，达到了和注释一样的效果

#!/bin/bash

# Shell关键字
# echo 打印文字到屏幕
# exec 执行另一个shell脚本
# read 标准读入
# expr 对整数型变量进行算数运算
# test 用于测试变量是否相等，为空，文件类型
# exit 退出

# 读入变量
read VAR
echo "VAR is $VAR"

# 计算变量
expr $VAR - 5

# 测试字符串
test "Hello"="hello"

# 测试整数
test $VAR -eq 10

# 测试目录
test -d ./shell

# 执行其他shell脚本
exec ./hello.sh

# 退出
exit

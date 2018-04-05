# coding:utf-8
"""
例1 某机床厂生产甲、乙两种机床，每台销售后的利润分别为4000元和3000元。
生产甲机床需用A、B机器加工，加工时间分别为每台2小时和1小时；生产乙机床需用A、B、C三种机器加工，加工时间为每台各一小时。若每天可用于加工的机器时数分别为 A 机器 10 小时、B 机器 8 小时和C 机器 7 小时，问该厂应生产甲、乙机床各几台，才能使总利润最大？
上述问题的数学模型：设该厂生产 x1台甲机床和 x2乙机床时总利润最大，则 x1, x2应满足
(目标函数) max z = 4*x1 + 3*x2
s.t.(约束条件):
    2*x1 + x2 <= 10
    x1 + x2 <= 8
    x2 <= 7
    x1, x2 > 0

这里x1 x2称为决策变量，s.t.意为subject to
"""

from scipy.optimize import linprog
import numpy as np

c = np.array([4, 3]) # 利润
a = np.array([[2, 1], [1, 1]])# 2*x1 + x2 <=10; x1 + x2 <=8的系数矩阵
b = np.array([10, 8]) # 矩阵等号右边的数值
'''
linprog(优化方程的系数， 约束矩阵的系数， 约束矩阵等号右边的值， bounds=每个决策变量的取值范围，元组的形式，当没有特别的约束时就可以写None)
还需要注意的是约束矩阵都需要写成xxx <= xx的形式
'''
res = linprog(c, a, b, bounds=((0, None), (0, 7)))
print(res.fun)
'''
函数返回一个scipy.optimize.OptimizeResult对象,包含了以下的数据
'''
'''
    fun: -0.0 函数的解，这里计算出的是最小值
message: 'Optimization terminated successfully.'
    nit: 0 迭代的次数
  slack: array([10.,  8.,  7.]) 松弛变量的值，每个松弛变量对应一个独立的约束
 status: 0
success: True
      x: array([0., 0.])
'''

'''
linprog()是用来求最小解的，所以要求同一个问题的最大解的时候c = -c，最终解为-x.fun
'''
m = linprog(-c, a, b, bounds=((0, None), (0, 7)))
print(-m.fun)

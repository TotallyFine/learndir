#coding:utf-8
#SIR模型是传染病模型最经典的模型，其中S表示健康的易感者，I表示感染者，R表示恢复者。SIR模型中，染病人群为传染的源头，每个染病的人都有一定的几率感染其他人，他自己也有一定的几率可以被治愈并免疫，或者死亡；易感人群一旦被感染就成了传染源。

#令S(0)表示初始的易感者人群的占比，I(0)表示初始的感染者的人群占比
#beta表示易感者人群的发病率（感染者的传播率）
#gamma表示感染者的治愈率

#那么得到
#dS/dt = -(beta * S * I)
#dI/dt = beta * S * I - gamma * I
#dR/dt = gamma * I

import scipy.integrate as spi
import numpy as np
#import pylab as pl

beta = 1.4247
gamma = 0.14286
TS = 1.0
ND = 70.0
S0 = 1-1e-6
I0 = 1e-6
INPUT = (S0, I0, 0.0)#SIR

def diff_eqs(INP, t):
    '''The main set of equations'''
    Y = np.zeros((3))
    V = INP
    Y[0] = - beta * V[0] * V[1]
    Y[1] = beta * V[0] * V[1] - gamma * V[1]
    Y[2] = gamma * V[1]
    return Y # 数值解

t_start = 0.0
t_end = ND
t_inc = TS
t_range = np.arange(t_start, t_end+t_inc, t_inc)#在t_start 到 t_end之间每隔t_inc取一个数字，然后组成数组
RES = spi.odeint(diff_eqs, INPUT, t_range)#接出参数为INPUT的方程diff_eqs间隔为t_range的数值解，是一个数组
print(RES)

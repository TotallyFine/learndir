# coding:utf-8
from .route import *
import re

def response_request(r):
    """
    r: Request实例
    return: 对应路径的html文档
    """
    path = r.parse_path()[0]
    if re.match('\S*(.css|.js)', path):
        return route_dict.get('code')(path)
    elif re.match('\S*(.jpeg|.jpg|.gif|.png|.ico)', path):# request for image
        return route_dict.get('image')(path)
    elif path not in route_dict.keys():
        return route_dict.get('error')() # 404 not found
    else:
        return route_dict.get(path)(r)# 将request传给对应的函数

if __name__ == '__main__':
    response_request()

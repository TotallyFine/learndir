# coding:utf-8
from .route import *

def response_request(r):
    """
    r: Request实例
    return: 对应路径的html文档
    """
    path = r.parse_path()[0]
    if path not in route_dict.key():
        return route_dict.get('error')() # 404 not found
    return route_dict.get(path)(r)# 将request传给对应的函数

if __name__ == '__main__':
    response_request()

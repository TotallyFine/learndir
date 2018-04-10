# coding:utf-8
from wsgiref.simple_server import make_server
from hello import application

# 创建一个服务器，IP为空，端口8001,处理函数是application
httpd = make_server('127.0.0.1', 8081, application)
print('Serving HTTP on port 8081...')

# 开始监听http请求
httpd.serve_forever()

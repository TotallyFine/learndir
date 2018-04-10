# coding:utf-8

def route_error():
    """
    404 not found page
    """
    header = 'HTTP/1.1 404 NOT FOUND'

def route_redirect(path):
    """
    302/301
    path: document's new path
    """
    header = 'HTTP/1.1 302 JUMP' + '\r\n' + 'Content-Type: text/html'
    location = 'Location: {}'.format(path)
    response = header + '\r\n' + location
    return response.encode('utf-8')

def route_index(r):
    """
    r: Request实例
    return: html文档
    """
    print('request for ', r.path)
    with open('../html/index.html', 'r') as f:
        body = f.read()
        header = 'HTTP/1.1 200 OK' + '\r\n' + 'Content-Type: text/html'
        response = header + '\r\n\r\n' + body
        return reponse.encode(encoding='utf-8')

"""
route_dict维护了一个 路径-返回对应路径文件函数 的字典
"""
route_dict = {
    '/': route_index,
    'error': route_error,
    'redirect': route_redirect,
}

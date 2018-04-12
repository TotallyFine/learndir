# coding:utf-8

html_prefix = '/home/jipuzhao/webapp/html'

def route_error():
    """
    404 not found page
    """
    header = 'HTTP/1.1 400 NOT FOUND' + '\r\n' + 'Content-Type: text/html'
    with open(html_prefix + '/404.html') as f:
        body = f.read()
        response = header + body
        return response.encode('utf-8')

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
    # print('request for ', r.path)
    with open(html_prefix + '/index.html', 'r') as f:
        body = f.read()
        header = 'HTTP/1.1 200 OK' + '\r\n' + 'Content-Type: text/html'
        response = header + '\r\n\r\n' + body
        return response.encode(encoding='utf-8')

def add_cookie(header, cookie=''):
    """
    header: 需要加上cookie的头部
    cookie: cookie内容
    return: 加上cookie之后的header

    不过显然，直接在cookie里写用户的username是不安全的。可以把username存在session里，假设session是一个字典，用户登录成功后随机生成一个长的字符串session_id作为key，username 作为value存入session中，然后把session_id作为cookie返回给浏览器，浏览器下次请求的时候带上cookie，服务器端拿到cookie之后去session中拿对应的数据即可
    """
    if header is None:
        header = 'HTTP/1.1 200 OK \r\nContent-Type: text/html\r\n'
    header += 'Set-Cookie: {}\r\n'.format(cookie)
    return header

def route_image(path):
    """
    path: request img path
    """
    header = 'HTTP/1.1 200 OK \r\nContent-Type: image/jpeg\r\n\r\n'
    p = path.split('/')[-1]
    img = open(html_prefix + '/' + p, 'rb')
    i = img.read()
    img.close()
    return header.encode('utf-8') + i

def route_code(path):
    """
    if request for css or js
    """
    header = 'HTTP/1.1 200 OK \r\nContent-Type: text/css,application/javascript\r\n\r\n'
    with open(html_prefix + '/' + path.split('.')[-1] + '/' + path.split('/')[-1]) as f:
        response = header + f.read()
        return response.encode('utf-8')


# route_dict维护了一个 路径-返回对应路径文件函数 的字典
route_dict = {
    '/': route_index,
    'image': route_image,
    'error': route_error,
    'redirect': route_redirect,
    'code': route_code,
}

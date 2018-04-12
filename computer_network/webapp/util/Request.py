# coding:utf-8

from urllib.parse import unquote, quote

class Request(object):
    """
    一个packet例子如下:
    POST /login HTTP/1.1
    Host: 127.0.0.1:8001
    User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:58.0) Gecko/20100101 Firefox/58.0
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
    Accept-Language: en-US, en;q=0.5
    Accept-Encoding: gzip, deflate
    Referer: http://127.0.0.1:8001/login
    Content-Type: application/x-www/form-urlencoded
    Content-Length: 27
    Cookie: D34h34toibefvna9wm
    Connection: keep-alive
    Upgrad-Insecure-Requests: 1

    username=admin&password=1234

    请求中换行是'\r\n',所以head 和 body之间是'\r\n\r\n'
    """
    def __init__(self, packet):
        self.content = packet
        self.method = packet.split()[0]
        self.path = packet.split()[1]
        self.body = packet.split('\r\n\r\n', 1)[1]

    def form_body(self):
        """
        一般来说在POST方法中才有body
        返回解析后的body，若返回的变量名为form_body,则可以使用form_body['username']来得到变量的值
        """
        return self._parse_parameter(self.body)

    def parse_path(self):
        """
        对路径进行解析，百度‘baidu’得到的路径如下
        https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&tn=ubuntuu_cb&wd=baidu&oq=get%25E6%2596%25B9%25E6%25B3%2595favicon&rsv_pq=804b74f00000cf21&rsv_t=e9f2LVSuRUBVndnAvBwzwOrVJAiX%2B24nwXW9c0vR%2BfpJF9gOyQbIV1%2FaCJsezC4w3g&rqlang=cn&rsv_enter=1&inputT=2706&rsv_sug3=34&rsv_sug1=4&rsv_sug7=100&rsv_sug2=0&rsv_sug4=3140
        ?后面代表的是参数，参数之间用&分割，key=value的形式
        解析后
        """
        index = self.path.find('?')# 若没有参数
        if index == -1:
            return self.path, {}
        else:
            path, query_string = self.path.split('?', 1)
            query = self._parse_parameter(query_string)
            return path, query

    @property
    def headers(self):
        """
        生成header属性，这个header属性中不包括第一行
        可以使用self.headers['Host']这样来获取相应的参数
        """
        header_content = self.content.split('\r\n\r\n', 1)[0].split('\r\n')[1:]
        result = {}
        for line in header_content:
            k, v = line.split(': ')
            result[quote(k)] = quote(v)
        return result

    @staticmethod
    def _parse_parameter(parameters):
        """
        静态类方法，对path中的参数进行解析
        """
        args = parameters.split('&')
        query = {}
        for arg in args:
            k, v = arg.split('=')
            query[k] = unquote(v)
        return query

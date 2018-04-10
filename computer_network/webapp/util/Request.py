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
        return self._parse_parameter(self.body)

    def parse_path(self):
        index = self.path.find('?')# 若没有参数
        if index == -1:
            return self.path, {}
        else:
            path, query_string = self.path.split('?', 1)
            query = self._parse_parameter(query_string)
            return path, query

    @property
    def headers(self):
        header_content = self.content.split('\r\n\r\n', 1)[0].split('\r\n')[1:]
        result = {}
        for line in header_content:
            k, v = line.split(': ')
            result[quote(k)] = quote(v)
        return result

    @staticmethod
    def _parse_parameter(parameters):
        args = parameters.split('&')
        query = {}
        for arg in args:
            k, v = arg.split('=')
            query[k] = unquote(v)
        return query

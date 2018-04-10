## Web Server Gateway Interface
底层的接受HTTP请求、解析HTTP请求、发送HTTP相应很繁重通常由底层的服务器来实现。而自己实现的代码重点在于生成HTML代码。
```python
def application(environ, start_response):
    start_response('200 OK', [('Content-Type', 'text/html')])
		return '<h1>Hello, World!</h1>'
		# return [b'<h1>Hello, World!</h1>'] 若为python3,则这样写
```
WSGI接口定义非常简单，只要求web开发者实现一个函数，就可以响应HTTP请求。其中:
 - environ: 一个包含所有HTTP请求信息的dict对象
 - start\_response: 一个发送HTTP响应的函数
 在application()中调用:
 ```python
 start_response('200 OK', [('Content-Type', 'text/html')])
 ```
就发送了HTTP相应的Header，Header只能发送一次，也就是只能调用一次start\_response().start\_response()接受两个参数，一个是HTTP相应码，一个是一组list表示的HTTP Header，每个Header用一个包含两个str的tuple表示。

有了WSGI，接下来就是从environ这个dict中拿到HTTP请求信息，然后构造HTML，并通过start\_response()发送报头，最后返回Body。

python内置了wsgiref模块可以实现这个功能。

### 框架
一个网站要处理很多的url请求，每一个url请求对应GET、POST等请求，一个最简单的方法是从environ变量中取出HTTP请求的信息，然后逐个判断
```python
def application(environ, start_response):
    method = environ['REQUEST_METHOD']
    path = environ['PATH_INFO']
		if method == 'GET' and path == '/':
						return handle_home(environ, start_response)
		if method == 'POST' and path == '/signin':
						return handle_signin(environ, start_reposne)
```
这样写下去的话代码无法进行维护。

SSH（SecureShell）是目前比较可靠的为远程登录会话和其他网络服务提供安全性的协议。利用SSH协议可以有效的防止远程管理过程中的信息泄漏问题。SSH也可以对传输的信息加密，也能防止DNS欺骗和IP欺骗。
（DNS 域名系统 Domain Name System，域名系统以分布式数据库的形式将域名和IP地址相互映射。DNS协议就是域名解析协议，DNS服务器将域名解析为地址，如果本地的DNS服务器没有某个网址的地址则向根服务器发出请求，就这样一直向下请求来获得地址，DNS欺骗原理 向目标机发送假的数据将其引导至假的网站上
IP欺骗涉及到计网的很多内容，下学期再看）
FTP、Pop、Telnet本质上都是不安全的，因为他们在网络上用明文传输数据、帐号和口令容易受到中间人攻击方式的攻击（另一台机器假冒服务器来接受数据）
http://os.51cto.com/art/201109/290385.htm



ssh分为ssh-client（ubuntu上默认安装），与ssh-server
sudo apt-get install openssh-server 安装ssh-server
dpkg -l | grep ssh查看所安装的和ssh有关的服务

ps -e | grep ssh查看ssh-server是否启动，如果有sshd的显示行则表示已经启动


sudo /etc/init.d/ssh start    sudo service ssh start 手动启动

sudo /etc/init.d/ssh stop 关闭ssh服务

ssh-server的配置文件位于/etc/ssh/sshd_config 这里可以定义ssh的服务端口，默认是22
如果要修改ssh所监听的端口，修改上述文件中的端口，（或者把配置文件中的PermitRootLogin without-password 加一个#注释掉，再增加一句“PermitRootLogin yes”），然后重启ssh服务

登录ssh ssh username@192.168.1.103 其中username@192.168.1.103是机器上的用户@机器的地址，需要密码

断开连接  exit

查看本机的ip ifconfig 有本地环回和连接到以太网上，看连接到以太网上的那个地址

可以使用一个路由器建立一个局域网，路由器连接到网络上，这样可以同时连接网络与服务器
如果网络断开，那么仍然可以通过nmap -sL 192.168.1.0/24或使用nmap的其他命令来查看局域网内的其他主机的ip地址

### ssh文件复制
 - 将文件/文件夹从远程Ubuntu拷贝到本地(scp)
 - scp -r username@192.169.0.102:/home/username/remotefile/txt

 - 将文件/文件夹从本地拷贝到远程Ubuntu
 - scp -r localfile.txt username@192.168.0.102:/home/username

### ssh 远程连接图形界面
1 服务器端的ssh必须运行转发X界面，在ssh服务器中找到/etc/ssh/sshd_config这个配置文件,其中有一行改为X11Forwarding yes,然后重启ssh服务，cd /etc/init.d下执行ssh restart
2 客户端配置，在/etc/ssh/ssh_config中，改为ForwardAgent yes   ForwardX11 yes    ForwardX11Trusted yes
3 在未连接之前执行xhost +服务器IP 允许服务器的X界面连接过来，然后执行ssh -X username@192.168.0.102 大写的X
4 连接到服务器之后执行 export DISPLAY=本地IP:0.0 192.168.0.100 （通过ifconfig查看）将ssh服务器的X显示重新定位到本地的0.0显示器中，也就是客户端上面
5 测试执行xclock

### SSH Server中/etc/ssh/sshd_config文件解释
 - Port 22 port用来设置sshd监听的端口，为了安全起见将其改为5位以上的陌生端口
 - Protocol 2,1 设置协议版本为SSH1或者SSH2,SSH1有漏洞选择SSH2
 - ListenAddress 0.0.0.0 ListenAddress用来设置sshd服务器，表示监听的主机适配卡，如果有两个IP，192.168.0.11 及 192.168.2.20,那么只想要开放192.168.0.11时就可以设置为ListenAddress 192.168.0.11.如果不设定的话表示本机拥有的所有的IP地址均接受SSH的访问

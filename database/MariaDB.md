## MariaDB
在Debian9上MySql已经被换为了MariaDB，所以sudo apt-get install mysql-server会安装上MariaDB所以不如使用apt-get install mariadb-server.两者是兼容的。

### 安装及设置
```shell
sudo apt-get install mariadb-server
```
在安装的过程中，将会请求配置MariaDB，设置root用户密码,若没有要求设置则密码为空。mariadb123

MariaDB安装包安装完成之后，启动数据库服务器守护进程，同时启用它，使得在下次开机的时候自动启动。

```shell
sudo systemctl start mariadb #启动服务
sudo systemctl enable mariadb #开机启动
sudo systemctl status mariadb
sudo systemctl restart mariadb # 重启
sudo service mysql stop # 停止服务
sudo /etc/init.d/mysqld stop # 停止服务
```
运行下面的脚本来保护数据库:
 - 设置root密码
 - 禁止远程root登录
 - 移除测试数据库
 - 移除匿名用户
 - 重载权限配置
```shell
sudo mysql_secure_installation
```
一旦数据库服务器受保护，可以使用下面的shell命令查看已安装版本和登录MariaDB
```shell
mysql -V
mysql -u root -p
```

配置MariaDB字符集。
```shell
mysql -u root -p
```
```MariaDB
SHOW CHARACTER SET; # 查看支持的所有字符集
SET NAMRS 'utf8'; # 设置utf-8编码
```

添加用户，设置权限。
```MariaDB
create user username@localhost identified by 'passwd'; # 创建用户
grant all on *.* to username@localhost identified by 'passwd';创建并授权
grant all privileges on *.* to username@'%' identified by 'passwd';# 授予外网登录权限，但不能二级授权
grant all privileges on *.* to username@'%' identified by 'passwd' with grant option; # 授权并可以二次授权
```
其中all privileges或者all可以改为select,insert,update,create,drop,index,alter,grant,reference,reload,shutdown,process,file.

### 使用
登录以后在MariaDB[(none)]>提示符下进行工作。

**新建数据库**

```SQL
CREATE DATABASE BooksDB;
```

### Python连接
Python连接MySQL和MariaDB需要MySQLdb模块:
```shell
pip install mysql-python
```
但是会提示mysql\_config not find的错误,是因为mysql-config相对于mysql-server/mariadb-server是另一个不同的package
```shell
sudo apt-get install libmysqlclient-dev #如果是mysql
sudo apt-get install libmariadbclient-dev #如果是mariadb
```
再执行:
```shell
pip install mysql-python
```

### 参考
[如何在Debian和Ubuntu上安装MariaDB](https://linux.cn/article-8283-1.html)

[Learn MySQL/MariaDB for Beginners - Part 1](https://www.tecmint.com/learn-mysql-mariadb-for-beginners/)

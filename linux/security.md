## 安全相关

### 入侵排查
**入侵原因**

一、检查隐藏账户及弱口令

1. 检查服务器系统及应用账户是否存在弱口令

检查管理员账户、MySql账户、tomact账户、网站后台管理员账户等密码设置是否较为简单

2. 使用last命令查看服务器近期的登录记录，确认是否有可疑IP登录

攻击者或者恶意软件往往会往系统中注入隐藏的系统账户，检查发现可疑账户的时候使用命令username -L <username> 禁用用户或者userdel -r <username>

3. 通过less /var/log/secure|grep 'Accepted'命令。查看是否有可疑IP登录

4. 检查系统是否采用默认管理端口

SSH、FTP、MySQL、Redis是否为默认的端口，容易被自动化工具进行攻击

5. 检查/etc/passwd文件，看是否有非授权账户登录

二、 检查恶意进程及非法端口

1. 运行netstat -antlp查看服务器是否有未被授权的端口被监听，查看对应的pid

若发现有非授权进程，运行ls -l /proc/$PID/exe 或者file /proc/$PID/exe 查看pid对应进程的文件路径，然后删除恶意文件

2. 使用ps -ef 和 top 命令查看是否有异常进程

运行以上命令发现有不断变化的非授权进程占用大量系统cpu或内存资源时，则可能为恶意进程 kill -9 <进程名>

三、 检查恶意程序和可疑启动项

1. 使用chkconfig --list 和 cat /etc/rc.local 查看开机启动项中是否有异常的启动服务

若有恶意进程，可使用chkconfig <服务名> off 关闭,同时检查 /etc/rc.local中是否有异常项，如有注释掉

2. 进入cron目录，查看是否存在非法定时任务脚本

看 /etc/crontab /etc/cron.d /etc/cron.daily  cron.hourly/ cron.monthly cron.weekly/ 如果是非正常的业务脚本，应注释掉任务内容或者删除
### 参考
[Linux 入侵类问题排查思路](https://cloud.tencent.com/document/product/296/9604)

[Linux中清除痕迹和隐藏自己](https://www.landui.com/help/show-3861.html)

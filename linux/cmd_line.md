## linux的一些命令与技巧

source 就是不需要重启就可以直接绑定一些文件的信息 source filaname
exit 推出终端
vim 打开vim编辑器
jupyter notebook 而不是 ipython notebook

sudo dpkg -i packge.deb  到deb包所在的位置，安装下载的deb包，packge为下载的包的名称
sudo dpkg -r packge.deb 卸载名为packge的软件 与上面的名字不同
sudo apt-get install -f 修复并自动安装所需要的依赖，当从deb包安装时可能有一些依赖没有安装此时程序不能正常运行，当出现这种情况的时候，运行此命令并再次	
	使用sudo dpkg -i packge.deb安装

poweroff 立刻关机
reboot 重启
shutdown 安全关机
运行.sh 文件http://blog.sina.com.cn/s/blog_54f82cc201010hfz.html

nautilus URL
nautilus -q 
 nautilus是Gnome下默认的文件管理器，相当于windows中的资源管理器
 1)第一种用法，通过命令行进入文件夹 nautilus 下载 直接进去下载文件夹
 2)第二用法关闭所有打开的文件管理器
 当主文件夹打不开的时候可以试一下 killall nautilus 来关闭所有关于nautilus的进程

### PATH命令
 echo $PATH来查看PATH环境变量
 /bin， /sbin，/usr/sbin， /usr/bin都是用于存放命令的路径 
 /sbin用于存放系统的命令 如shutdown等 只有管理员才能用
 /bin用于存放一些普通的基本命令如ls等 普通用户都可以用
 /usr/bin用于存放安装的一些软件的运行脚本 如python2.7 python3等
 /usr/sbin用于存放一些用户安装的系统管理的必备程式


### 使用anaconda控制python包的版本
 anaconda有错误： 1.删除整个文件夹 2. sudo gedit ～/.bashrc 把ananconda的PATH删除 3. 在新的终端上查看是否被删除
 使用conda相关命令来创建新的环境在我的电脑上会遇到玄学错误，无法解决。所以使用anaconda-navigator命令来进入GUI界面创建以及进行包的管理。
 执行python --version查看python版本 ubuntu16.04自带的是2.X安装anaconda后一般会变成3.x
 conda info --envs 查看现有的环境，环境名称前带有星号的就是当前的环境
 source activate <name> 切换到指定的环境
 deactivate 切换到系统的环境
 conda create -n <name> --clone <exist> 复制一个环境
 conda remove - n <name> --all 删除一个环境
 利用conda创建新的python环境
  conda create -n <name> python=2

### 安装SimpleITK
在anaconda navigator中无法查找到SimpleITK，还有一些包也无法在界面中查找到所以先登录anaconda.org 搜索SimpleITK，进入页面有相关的安装方式
安装的时候注意安装到相应的环境中，conda install -n <env> -n simpleitk simpleitk
然后import SimpleITK来进行检查
   
   
### 提示/boot空间不足的解决方法
通过dpkg --get-selections |grep linux-image查看已经安装的各个版本
uname -sr查看本机正在使用的版本
sudo apt-get purge linux-image-4.10.0-37-generic 删除不用的内核
也可以自动使用sudo apt autoremove --purge来删除那些系统不再需要的内核和软件包

### 管道命令
管道命令允许把一个命令的输出结果作为输入传给另一个命令。grep命令用于在指定的地方搜索输入字符串。ls | grep note 这样就可以查找名字包含note的文件。

### 通配符
\*是一个可以匹配任何东西的通配符。rm really\*name 可以删除任何以really开头以name结尾的文件

### 输出重定向
\>字符可以把一个命令的输出重定向到一个文件，而不需要额外使用另一个命令。比如 ls > file 将该目录下的文件和文件夹输入到file文件中。

### 命令行历史
bash会记录使用过的命令行的历史。使用history打印

### 目录
~代表当前用户的主目录，可以使用cd~切换到自己的主目录

### 后台运行
在命令后加一个 & 可以在后台执行

### 条件执行
可以使用bash一次执行两个命令。第二个命令只有当第一个命令成功运行完毕之后才会运行。用&&进行分隔即可。
sleep命令会以秒为单位接受一个参数，然后倒计时最后结束。单独来用这个命令没有什么用处，但是可以用来对让一个命令延缓执行。 

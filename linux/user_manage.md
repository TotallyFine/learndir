


### 保存用户信息的文件
http://blog.csdn.net/yaofeino1/article/details/54616440
使用cat /etc/passwd  在linux中，/etc/passwd文件中的每个用户都有一个对应的记录，记录每个用户的基本属性，这个文件对所有的用户都可读
而 /etc/shadow文件是passwd的一个影子，其中的数据由/etc/passwd自动产生，但是只有管理员才能查看修改
执行cat /etc/passwd之后可以看到如下的数据
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usrsbin/nologin
......
每行被冒号分为七个部分，用户名:口令:用户标志号:组标志号:注释性描述:主目录:登录Shell
 + 用户名 是代表用户帐号的字符串，通常不超过8个字符登录名中不能有冒号，因为这里 是用冒号作为分隔符的，并且也最好没有. - + 
 + 口令 /etc/passwd对所有用户可读，所以这里存放的是加密后的口令用x表示，而真正的用户密码在 /etc/shadow中
 + 用户标志号 是一个整数，系统内部用来标志用户，一般情况下与用户名一一对应。多个用户的标志号可以相同，这时系统时他们为同一个用户，但是他们可以有不同的口令、不同的主目录以及不同的登录Shell，0是root 1-99由系统占用，普通用户的标志号从100开始
 + 主目录 用户的起始工作目录，用户登录后的目录，在大多数的系统中，各用户的的主目录都被组织到一个特定的目录下各用户对自己的主目录有读、写、执行（搜索）的权限，其他的用户对此目录则是根据情况而定
 + 登录Shell 用户登录后要启动一个进程，负责将用户的操作传给内核，这个进程是用户登录到系统之后运行的命令解释器或某个特定的程序，Shell是用户与内核之间的接口，系统管理员可以根据系统情况和用户习惯给某个用户指定Shell，如果不指定则系统使用sh作为登录Shell，也就是这个字段的值是 /bin/sh

如果执行sudo cat /etc/shadow则可以查看 /etc/shadow文件，会看到如下
root:!:17445:0:99999:7:::
daemon:*:17379:0:99999:7:::
......
登录名:加密口令:最后一次修改时间:最小时间间隔:最大时间间隔:警告时间:不活动时间:失效时间:标志
 + 登录名和/etc/passwd中的相同
 + 口令存放的是加密后的用户口令，如果为空则没有口令，登录不需要口令，*代表帐号被锁定，双叹号表示这个密码过期了，其他的符号表示用其他的加密方法进行加密的
 + 其他的就看原链接
 
### 用户管理
root帐号通常用于维护和管理，在Unix/Linux安装的过程中，系统会自动创建许多用户帐号，而这些默认的用户称为标准用户，在大多数的Unix Linux中都不推荐直接用root帐号登录

 + 查看当前用户 whoami
 + 查看登录的用户 who
 + 退出登录账户 exit，如果是图形界面将退出终端，如果是使用ssh远程登录则退出登录账户，如果是切换后的登录用户，则返回上一个登录帐号
 + 切换用户 su，su root ； su 普通用户 ； ubuntu提供了可以直接使用管理员权限执行命令的sudo功能，所以不需要切换，提高了安全性，使用su切换用户不会切换工作目录（当前的目录），使用su - 普通用户/root会切换到该用户的目录
 + 添加删除组帐号 groupadd groupdel cat /etc/group 查看组、
 + 添加用户帐号 useradd -d main_path username -g groupname -m，-d是指定用户登录时的主目录，如果不使用该参数则系统会在/home下自动建立与用户同名的目录，-m自动自动建立目录，-g指定组名称，如果创建的时候不指定组名称则系统会自动创建一个和用户名一样的组名
 + 设置用户密码 sudo passwd username
 + 删除用户 userdel，userdel username 不会删除用户的主目录，userdel -r username 删除主目录
 + 修改文件权限   




来查看所有的用户 使用cat /etc/group 来查看所有的用户组
root:x:0:
daemon:x:1:
......
jipuzhao:x:1000
第一个是用户组名，最后一个是该组的用户
创建用户组 groupadd [groupname]
删除用户组 groupdel [groupname]

修改某用户对文件的权限
 + 授予某用户对某个文件的权限 chmod o+w filename
 + 删除权限 chmod o-r filename
 + o是其他的用户，u代表所有者，g代表所有者所在的族群，g代表所有人
 + r读取 w写 x可以被执行

### 查看用户的权限
 - 使用ls -l可以查看当前目录下的文件的权限情况
 - total 4 代表一共4K
 - 第一个字符，d代表目录，-代表普通文件，l代表连接文件，b代表设备文件
 - 第一组权限说明代表文件所有者
 - 第二组代表文件文件所有者所在的用户组
 - 第三组代表其他用户
 - 若该文件为目录则跟着的数字是子目录数
 - 用户名、用户所在的群组
 - 文件大小
 - 文件最后修改的时间

### 文件夹的r与x的区别
 - linux下目录可以看成是一种特殊的文件，它相当于一个列表，保存着目录下的子目录和文件，r代表这个文件可读，可读的意思是其他的程序可以访问这个文件，比如ls，所以没有了r权限执行ls将不能看到这个文件夹
 - w代表修改这个文件，就是修改这个文件夹的名字、删除文件夹和子目录等
 - 

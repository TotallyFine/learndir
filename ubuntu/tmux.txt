### tmux 是一个能在一个终端窗口中运行多个终端会话的工具。
 - 为了使自身的快捷键和其他的软件不冲突，tmux设计了快捷键前缀，使用快捷键的时候需要先按下快捷键前缀，然后按下快捷键。
 - Tmux默认的快捷键前缀是Ctrl+b。假如想要通过快捷键列出Tmux中的会话（对应的快捷键是s）：
 - 按下组合键 Ctrl+b
 - 放开组合键 Ctrl+b
 - 按下s键

### Tmux的配置文件
 - 每当开启一个新的会话的时候Tmux都会先读取~/.tmux.conf这个文件，里面存放的就是对Tmux的配置
 - 如果希望配置文件能够立即生效，可以在配置文件里加入
 - bind R source-file ~/.tmux.conf; display-message "Config reloaded.."

### 开启多个窗格
 - 创建一个竖直放置的窗格 Ctrl+b %
 - 创建一个水平放置的窗格 Ctrl+b "
 - 在多个窗口之间切换Ctrl+b 方向键

### 窗口
 - 在Tmux中窗口是一个窗格容器，可以将多个窗格放在一个窗口之中
 - 所有窗口都会在最下面的那一行显示
 - 0:vim 1:bash类似这样的
 - Ctrl+b c 创造新的窗口
 - Ctrl+b 数字 切换到对应的窗口
 - Ctrl+b Alt+方向键 调整窗格的大小，但是整个窗口的大小是不变的

### 会话
 - 一个会话中可以包含多个窗口。可以为一个项目指定一个专用的会话
 - tmux new -s <name-of-my-session> 在终端进入新的会话
 - Ctrl+b : 再接着输入 new -s <name-of-my-new-session>
 - 只要没有显式地关闭会话，否则在关闭计算机前都会存在，可以自由地切换会话
 - Ctrl+b s 显示当前的会话
 - 列表中的每一个会话都有一个ID，这个ID从0开始，在显示当前会话的界面按下对应的数字就可以进入会话。
 - 如果已经创建了一个或者多个会话，但是还没有运行tmux，可以输入下面的命令来接入已经有的会话
 - tmux attach

 - tmux ls  显示所有的会话
 - tmux a 接入上一个会话
 - tmux kill-session -t <session-name/session-ID>
 - tmux kill-server 销毁会话并停止tmux

tmux还有很多的功能比如使用ssh远程共享会话等，以及使用到系统的剪贴板等等


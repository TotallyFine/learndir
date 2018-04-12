## Socket

### UDP

Communication between two thread using UDP, before send message, should bind destination address(IP) to this packet.After packet sended, Internet will make it to destination's socket, and destination's host check this packet, let it go right thread.

Once create socket, give it a port name as identifier.One thread may have one more socket, also ,many port name.

### TCP

TCP is a protocol face to link, before send message, should estabilsh a TCP link which associate client and server's ip:port.Different form UDP, TCP send message throuh TCP link, without binding address every time.

For TCP server:
1. TCP server should run before client.
2. Server should has a special socket for accept someone's initial touch.When client program start,it attempt to connect with this special socket.After three-way handshaking, server creates a new socket for communication with this client.The new created socket called connection socket.Client doesn't need to create a new socket, the original socket connect to connection socket.

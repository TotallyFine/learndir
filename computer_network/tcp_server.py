# coding:utf-8
from socket import *

server_port = 12000
server_socket = socket(AF_INET, SOCK_STREAM) # connection socket
server_socket.bind(('', server_port))
server_socket.listen(1) # only listen to one client's request

print('The server is ready to receive.')

while(True):
    connection_socket, addr = server_socket.accept()
    sentence = connection_socket.recv(1024)
    modified_sentence = sentence.upper()
    print('modified sentence:', modified_sentence)
    connection_socket.send(modified_sentence)
    connection_socket.close()

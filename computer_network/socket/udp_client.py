# coding:utf-8
from socket import *

server_name = 'localhost' # can be ip or host name
server_port = 12000

client_socket = socket(AF_INET, SOCK_DGRAM)
# using raw_input all input will be string, input() should add'message',and number will be int or float
message = raw_input('Input lowercase sentence:')

client_socket.sendto(message, (server_name, server_port))
# server_address contains IP and port.2048 means cache size is 2048.
modified_message, server_address = client_socket.recvfrom(2048)

print(modified_message)
client_socket.close()

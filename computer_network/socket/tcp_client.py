# coding:utf-8
from socket import *

server_name = 'localhost'
server_port = 12000

client_socket = socket(AF_INET, SOCK_STREAM) # AF_INET means use IPv4, SOCK_STREAM means use TCP
client_socket.connect((server_name, server_port))

sentence = raw_input('Input lower case sentence.')

client_socket.send(sentence)
modified_sentence = client_socket.recv(1024)

print('From server:', modified_sentence)

client_socket.close()

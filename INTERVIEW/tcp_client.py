#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket


# host 为服务器ip地址
# port 为端口号码
# bufsize是缓冲区大小
host = '127.0.0.1'
port = 23456
bufsize = 1024
ADDR = (host, port)

tcpCliSock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
tcpCliSock.connect(ADDR)


while True:
    data = raw_input('>')
    if not data:
        break
    tcpCliSock.send(data)
    data = tcpCliSock.recv(bufsize)
    if not data:
        break
    print data

tcpCliSock.close()

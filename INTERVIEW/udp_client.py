#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket

##host = '219.223.241.227'
host = '127.0.0.1'
port = 23456
bufsiz = 1024
ADDR = (host,port)

udpCliSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    data = raw_input('> ')
    if not data:
        break
    udpCliSock.sendto(data,ADDR)
    data,ADDR = udpCliSock.recvfrom(bufsiz)
    if not data:
        break
    print data

udpCliSock.close()

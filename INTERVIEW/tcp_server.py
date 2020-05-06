#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
from time import ctime

'''
host 为空表示bind可以绑定到所有有效地址上
port 必须要大于1024
bufsize 为缓冲区 设置为1K
'''

host = ''
port = 23456
bufsize = 1024
ADDR = (host, port)

tcpSerSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcpSerSock.bind(ADDR)
tcpSerSock.listen(5);


try:
    while True:

        print 'waiting for connection'
        tcpSerSock, addr = tcpSerSock.accept()
        print '...connect from ', addr

        while True:
            data = tcpSerSock.recv(bufsize)
            if not data:
                break
            tcpSerSock.send('[%s] %s' %(ctime(), data))
except BaseException, e:
    tcpSerSock.close()
    
        

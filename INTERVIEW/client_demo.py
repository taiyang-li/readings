import socket

s = socket.socket()  
s.bind(('xxx.xxx.xxx.xxx', xxxx))
cs, address = s.accept()
print 'got connect from', address
cs.send('byebye')
ra = cs.recv(512)
print ra
cs.close()


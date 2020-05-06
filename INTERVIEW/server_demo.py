import socket
s = socket.socket()
s.connect(('xxx.xxx.xxx.xxx', xxxx))
s.send('hihi')
s.close()
print 'the data received is', data

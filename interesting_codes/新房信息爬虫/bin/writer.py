#!/usr/bin/env python
# -*- coding: utf-8 -*

import sys
import os
from time import strftime, gmtime, localtime

class Writer(object):
    def __init__(self, path):
        self.path = path # 写文件的路径
        self.suffix = strftime("%Y%m%d", localtime())
        self.file = '%s.%s' % (self.path, self.suffix)
        self.handler = open(self.file, 'a')

    def __del__(self):
        self.handler.flush()
        self.handler.close()

    def write(self, msg):
        if isinstance(msg, unicode):
            msg = msg.encode('utf-8')
        self.handler.write('%s\n' % (msg))

if __name__ == '__main__':
    writer = Writer('../data/test.log')
    for i in range(100):
        writer.write('hello world %d' % (i))
    print "done"

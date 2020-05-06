#!/usr/bin/env python
# -*- coding: utf-8 -*

import sys
import os
import json
import logging
from time import strftime, gmtime, localtime
from pymongo import MongoClient

class MongodbWriter(object):
    def __init__(self, host='localhost', port=27017, db='maifang', table='newhouse'):
        self.host = host
        self.port = port
        self.client = MongoClient(self.host, self.port)
        self.collection = self.client[db][table]

    def write(self, msg):
        if isinstance(msg, unicode):
            msg = msg.encode('utf-8')
        try:
            d = json.loads(msg)
            url = {'url': d['url']}
            self.collection.update(url, d, upsert=True)
        except Exception, e:
            logging.error('msg:%s, error:%s' % (msg, str(e)))

if __name__ == '__main__':
    writer = MongodbWriter()
    for i in range(100):
        d = {}
        d['name'] = '中国%d' % (i)
        writer.write(json.dumps(d))

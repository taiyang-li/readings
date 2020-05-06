#!/usr/bin/env python 

import uuid
import redis

def create_num(num, length):
    result = set()
    while num > 0:
        raw_code = uuid.uuid1()
        active_code = str(raw_code).replace('-', '')[:length]
        if active_code not in result:
            result.add(active_code)
            num -= 1

    return result

active_codes = create_num(200, 16)
 
pool = redis.ConnectionPool(host='localhost', port=6379)
r = redis.Redis(connection_pool=pool)
active_codes_key = "active_codes"
for code in active_codes:
    print "push %s" % (code)
    r.lpush(active_codes_key, code)

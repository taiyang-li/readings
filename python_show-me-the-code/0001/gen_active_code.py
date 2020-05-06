#!/usr/bin/env python 

import uuid

def create_num(num, length):
    result = set()
    while num > 0:
        raw_code = uuid.uuid1()
        active_code = str(raw_code).replace('-', '')[:length]
        if active_code not in result:
            result.add(active_code)
            num -= 1

    return result

print(create_num(10, 10))


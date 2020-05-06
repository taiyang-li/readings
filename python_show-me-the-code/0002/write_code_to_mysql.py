#!/usr/bin/env python

import MySQLdb
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

db = MySQLdb.connect(host='localhost', port=3306, user='root', passwd='')
cursor = db.cursor()

# create database 
cursor.execute("create database if not exists test")
cursor.execute("use test")


# create table
sql = '''
CREATE TABLE IF NOT EXISTS `active_code`(
   `id` INT UNSIGNED AUTO_INCREMENT,
   `code` VARCHAR(64) NOT NULL,
   PRIMARY KEY ( `id` )
)ENGINE=InnoDB DEFAULT CHARSET=utf8; 
'''
cursor.execute(sql)

# clear table
sql = 'delete from active_code'
cursor.execute(sql)
db.commit()

# insert active_codes
active_codes = create_num(200, 16)
for code in active_codes:
    sql = 'insert into active_code (code) values (\'%s\')' % (code)
    cursor.execute(sql)
    db.commit()

db.close()















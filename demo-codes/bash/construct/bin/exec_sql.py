#!/usr/bin/env python
# -*- coding:gb18030 -*-

import os
import sys
import shutil
import MySQLdb
from conf import db_by_file, table_by_file

def show_usage():
    print "exec_sql.py <userid> <planid>"
    sys.exit(-1)

def gen_count_sql(table, userid):
    table_name = table[0]
    is_shard = table[1]
    if is_shard:
        table_no = userid / 4 % 8
        table_name += str(table_no)
    count_sql = "select count(*) from %s where userid = %d;" % (table_name, userid)
    return count_sql

def exec_sql(data_type, in_path, out_path, userid):
    if data_type not in db_by_file or data_type not in table_by_file:
        print "unknown data_type %s" % (data_type)
        return -1

    db = db_by_file[data_type]
    host = db[0]
    port = eval(db[1])
    user = db[2]
    passwd = db[3]
    tables = table_by_file[data_type]

    try:
        # connect and set names
        db = MySQLdb.connect(host=host, port=port, user=user, passwd=passwd)
        cursor = db.cursor();
        cursor.execute("set names gbk;")
        db.commit()

        with open(in_path, 'r') as in_f:
            with open(out_path, 'w') as out_f:
                # execute clear and insert
                for line in in_f.readlines():
                    sql = line.strip("\n")
                    cursor.execute(sql)
                    db.commit()

                # execute count
                for table in tables:
                    count_sql = gen_count_sql(table, userid)
                    cursor.execute(count_sql)
                    data = cursor.fetchone()
                    count = str(data[0])
                    out_f.write("%s\t%s\n" % (count_sql, count))
        
        # check numbers
        cursor.close()
        db.close()

    except MySQLdb.Error,e:
        print "Mysql Error %d: %s, sql: %s" % (e.args[0], e.args[1], sql)

if len(sys.argv) < 3:
    show_usage()

userid = int(sys.argv[1])
planid = int(sys.argv[2])
curr_dir = os.path.split(os.path.realpath(__file__))[0] 
in_dir = "%s/../data/sql.%d.%d" % (curr_dir, userid, planid)
out_dir = "%s/../data/count.%d.%d" % (curr_dir, userid, planid)

if not os.path.exists(in_dir):
    print "%s not exists, exit now" % (in_dir,)
    sys.exit(-1);

if os.path.exists(out_dir):
    shutil.rmtree(out_dir)
os.mkdir(out_dir)

in_file_list = os.listdir(in_dir)
for in_file in in_file_list:
    data_type = in_file.split(".")[0]
    in_path = "%s/%s" % (in_dir, in_file)
    out_path = "%s/%s.count" % (out_dir, data_type)
    exec_sql(data_type, in_path, out_path, userid)

print "exec_sql done"

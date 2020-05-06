#!/usr/bin/env python
# -*- coding:gb18030 -*-

import os
import sys
import shutil
from conf import table_by_file, schema_by_file

def show_usage():
    print "data2sql.py <userid> <planid>"
    sys.exit(-1)

def output_sql(data_type, in_path, out_path, userid):
    if data_type not in table_by_file or data_type not in schema_by_file:
        print "unknown data_type %s" % (data_type)
        return -1

    tables = table_by_file[data_type]
    schema = schema_by_file[data_type]
    try:
        in_f = open(in_path, 'r')
        out_f = open(out_path, 'w')
    except IOError, e:
        print "open file failed, data_type: %s, in_path: %s, out_path: %s" % (data_type, in_path, out_path)
        return -2

    for table in tables:
        ret = do_output_sql(table, schema, in_f, out_f, userid)
        if ret != 0:
            print "do_output_sql failed, ret: %d, data_type: %s, in_path: %s, out_path: %s" % (ret, data_type, in_path, out_path)
            return -3

    in_f.close()
    out_f.close()
    return 0

def do_output_sql(table, schema, in_f, out_f, userid):
    clear_sql = gen_clear_sql(table, userid)
    if clear_sql == "":
        print "gen_clear_sql failed, table: %s" % (str(table))
        return -1
    out_f.write(clear_sql)
    out_f.write("\n")

    sql_header = gen_sql_header(table, userid)
    if sql_header == "":
        print "gen_sql_header failed, table: %s" % (str(table))
        return -2

    count = 0
    sql_tail = ""
    in_f.seek(0, os.SEEK_SET)
    for line in in_f.readlines():
        line = line.strip("\n")
        sql_value = gen_sql_value(table, schema, line)
        if sql_value == "":
            print "gen_sql_value failed, table: %s, schema: %s, line: %s" % (str(table), str(schema), line)
            return -3

        if count != 0:
            sql_tail += ", "
        sql_tail += sql_value

        count += 1
        if count == max_values_per_sql:
            sql = "%s %s;" % (sql_header, sql_tail)
            out_f.write(sql)
            out_f.write("\n")
            count = 0
            sql_tail = ""

    if count > 0:
        sql = "%s %s;" % (sql_header, sql_tail)
        out_f.write(sql)
        out_f.write("\n")
    return 0

def gen_clear_sql(table, userid):
    table_name = table[0]
    is_shard = table[1]
    if is_shard: 
        table_no = userid / 4 % 8
        table_name += str(table_no)
    clear_sql = "delete from %s where userid = %d;" % (table_name, userid)
    return clear_sql

def gen_sql_header(table, userid):
    table_name = table[0]
    is_shard = table[1]
    table_fields = table[2]
    if is_shard: 
        table_no = userid / 4 % 8
        table_name += str(table_no)
    sql_header = "insert into %s (" % (table_name)
    for idx, field in enumerate(table_fields):
        if idx == len(table_fields) - 1:
            sql_header += field
        else:
            sql_header += field
            sql_header += ", "
    sql_header += ") values"
    return sql_header

def gen_sql_value(table, schema, line):
    value_list = line.split("\t")
    if len(value_list) < len(schema):
        print "unmatched size: line: %s, schema: %s" % (line, str(schema))
        return ""

    value_map = {}
    for idx, field in enumerate(schema):
        value = value_list[idx]
        value_map[field] = value

    fields = table[2]
    sql_value = "("
    for idx, field in enumerate(fields):
        if field not in value_map:
            return ""
        if value_map[field] == "None":
            sql_value += "NULL"
        else:
            sql_value += "'%s'" % (value_map[field]) 
        if idx != len(fields) - 1:
            sql_value += ", "
    sql_value += ")"
    return sql_value

if len(sys.argv) < 3:
    show_usage()

userid = int(sys.argv[1])
planid = int(sys.argv[2])
curr_dir = os.path.split(os.path.realpath(__file__))[0] 
max_values_per_sql = 500
in_dir = "%s/../data/data.%d.%d" % (curr_dir, userid, planid)
out_dir = "%s/../data/sql.%d.%d" % (curr_dir, userid, planid)

# print userid, planid, curr_dir, in_dir, out_dir
if not os.path.exists(in_dir):
    print "%s not exist, exit now" % (in_dir,)
    sys.exit(-1)

if os.path.exists(out_dir):
    shutil.rmtree(out_dir)
os.mkdir(out_dir)

in_file_list = os.listdir(in_dir)
for in_file in in_file_list:
    data_type = in_file
    in_path = "%s/%s" % (in_dir, in_file)
    out_path = "%s/%s.sql" % (out_dir, in_file)
    print "out_sql, data_type: %s" % (data_type)
    output_sql(data_type, in_path, out_path, userid)

print "data2sql done"


#!/bin/bash
# awk 基本用法

echo -e "line1\nline2" | awk 'BEGIN{print "START"} {print} END{print "END"}'

echo | awk '{var1="v1"; var2="v2"; var3="v3"; print var1, var2, var3;}'

# NR行号  NF字段数量
echo -e "line1 f2 f3\nline2 f4 f5\nline3 f6 f7" | awk '{print "Line no: "NR", No of fields: "NF, "$0="$0,"$1="$1, "$2="$2, "$3="$3}'

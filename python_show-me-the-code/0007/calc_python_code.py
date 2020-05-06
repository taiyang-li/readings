#!/usr/bin/env python
# coding: utf-8

import os
import re

lines = {'comment': 0, 'blank': 0, 'code': 0}
in_comment_block = False
in_string_block = False
pattern_contain_3quote = r"""'''|\"\"\""""
pattern_contain_6quote = r"""'''.*'''|\"\"\".*\"\"\""""

def is_in_comment_block(line):
    global in_comment_block
    global in_string_block

    # 该行不包含''' 或者"""
    if re.search(pattern_contain_3quote, line) is None:
        return in_comment_block
    
    # 该行包含一对'''或者"""
    if not re.search(pattern_contain_6quote, line) is None:
        if line.startswith('"""') or line.startswith("'''"):
            return True
        else:
            return False

    if not in_comment_block and not in_string_block:
        if line.startswith('"""') or line.startswith("'''"):
            in_comment_block = True
            return True
        else:
            in_string_block = True
            return False
    elif in_comment_block:
        in_comment_block = False
        return True
    elif in_string_block:
        in_string_block = False
        return False
    else:
        return False

    
def count_lines(filepath):
    with open(filepath) as f:
        for line in f.readlines():
            line = line.strip()
            if line == '':
                lines['blank'] += 1
            elif line.startswith('#') or is_in_comment_block(line):
                lines['comment'] += 1
            else:
                lines['code'] += 1

for topdir, dirs, files in os.walk('..'):
    for name in files:
        ext = os.path.splitext(name)[1]
        if ext == '.py':
            filepath = "%s/%s" % (topdir, name) 
            count_lines(filepath)

print lines


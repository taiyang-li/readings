#!/usr/bin/env python
# -*- coding:gb18030 -*-

import os
import sys

table_by_file = {
        'user': [[your_table_name, False, ['userid', 'username']]],
        }

src_schema_by_file = {
        'user': ['userid', 'username'],
        }

dst_schema_by_file = {
        'budget'
        }

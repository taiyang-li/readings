#!/usr/bin/env python
# -*- coding: utf-8 -*

import sys
import os
import json
from time import strftime, gmtime, localtime
from mongodb_writer import MongodbWriter

today = strftime("%Y%m%d", localtime())
path = '../data/newhouse.%s' % (today)
writer = MongodbWriter()
with open(path, 'r') as f:
    for line in f:
        line = line.strip()
        writer.write(line)

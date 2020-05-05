#!/bin/bash
# —∞’“»Ì¡¨
touch log.1
ln -sf log.1 log

# —∞’“»Ì¡¨1
ls -l | grep "^l" | awk '{print $8}'
ls -l | grep "^l" | awk '{print $10}'

# —∞’“»Ì¡¨Ω”2
find . -type l

#!/bin/bash
# Ѱ������
touch log.1
ln -sf log.1 log

# Ѱ������1
ls -l | grep "^l" | awk '{print $8}'
ls -l | grep "^l" | awk '{print $10}'

# Ѱ��������2
find . -type l

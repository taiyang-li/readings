#!/bin/bash
# ʹ��md5

# �����ļ�md5
md5sum log > log.md5

# У���ļ�md5 
md5sum -c log.md5

## ����Ŀ¼md5
#md5sum -r ./ > path.md5
#
## У��Ŀ¼md5
#md5sum -c path.md5

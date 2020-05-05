#!/bin/bash
# 使用md5

# 生成文件md5
md5sum log > log.md5

# 校验文件md5 
md5sum -c log.md5

## 生成目录md5
#md5sum -r ./ > path.md5
#
## 校验目录md5
#md5sum -c path.md5

#!/bin/bash
# ʹ��dd �� split 

dd if=/dev/zero of=data.file bs=100k count=3

split -b 100k data.file -d -a 4 "split_data."

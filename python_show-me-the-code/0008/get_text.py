#!/usr/bin/env python 
# -*- coding: utf-8 -*

from bs4 import BeautifulSoup
import requests

# r = 'http://www.toutiao.com/a6389133537292304642/'
r = 'http://blog.csdn.net/laozhongyizhenggu/article/details/74164780'
headers = {'user-agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36'}
url = requests.get(r,headers=headers)
soup = BeautifulSoup(url.text,'lxml')
print(soup.get_text())


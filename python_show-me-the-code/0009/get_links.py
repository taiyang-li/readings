#!/usr/bin/env python 
# -*- coding: utf-8 -*

from bs4 import BeautifulSoup 
import urllib
import urllib2
import sys
reload(sys)
sys.setdefaultencoding('utf8')

def find_all_link(url):
    proto, rest = urllib.splittype(url)
    domain = urllib.splithost(rest)[0]

    html = urllib2.urlopen(url).read()
    a = BeautifulSoup(html).findAll('a')
    alist = [i.attrs['href'] for i in a if i.attrs['href'][0] != 'j']
    alist = [proto + '://' + domain + i if i[0] == '/' else url + i if i[0] == '#' else i for i in alist]
    return alist

print find_all_link('https://www.zhihu.com/')



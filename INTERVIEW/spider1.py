#!usr/bin/python
#coding:utf-8
 
#---------------------------------------
# 百度贴吧小爬虫
# 版本 : 0.1
# Create By : jfxwc
# Create Day: 2008-05-10
# 编程语言 : Python 2.5
#---------------------------------------
# 简介 : 偶尔看百度贴吧，想保存下来慢慢看，于是有了这个小软件
#        输入带分页的地址，去掉最后面的数字，设置一下起、末贴数即可下载。
#---------------------------------------
 
import string, urllib
 
#定义 bd（百度）函数
def bd(url,PostBegin,PostEnd):
    for i in range(PostBegin, PostEnd ,50):
        sName = string.zfill(i,6) + '.html'
        print 'working..... ' + sName
        f = open( string.zfill(sName,6),'w+')
        m = urllib.urlopen(url + str(i)).read()
        f.write(m)
        f.close()
 
 
#-------- 在这里输入参数  ------------------
# 这个是《青囊尸衣》百度贴吧的地址。
bdurl = 'http://tieba.baidu.com/f?z=360426363&ct=335544320&lm=0&sc=0&rn=50&tn=baiduPostBrowser&word=%C7%E0%C4%D2%CA%AC%D2%C2&pn='
iPostBegin = 1150
iPostEnd = 1250
#-------- 在这里输入参数  ------------------
 
 
#调用
bd(bdurl,iPostBegin,iPostEnd)


#coding:utf-8
 
#---------------------------------------
# 网易新闻小爬虫
# 版本 : 0.1
# Create By : jfxwc
# Create Day: 2008-03-19
#---------------------------------------
# 简介 : 通过分析 www.163.com ，分析其中以 News.163.com 开头的链接
#        获取 各链接的内容，并合并到 1.txt 以便查看各新闻。
#        由于 163 新闻的格式不是非常统一，所以只能说大部分可以自动下载。
#---------------------------------------
 
import re, urllib
 
strTitle = ""
strTxtTmp = ""
strTxtOK = ""
 
f = open("163News.txt", "w+")
 
m = re.findall(r"news\.163\.com/\d.+?<\/a>",urllib.urlopen("http://www.163.com").read(),re.M)
for i in m:
    testUrl = i.split('"')[0]
    if testUrl[-4:-1]=="htm":
 
    # 合并标题头内容
        strTitle = strTitle + "\n" + i.split('"')[0] + i.split('"')[1]
 
    # 重新组合链接
        okUrl = i.split('"')[0]
        UrlNews = ''
        UrlNews = "http://" + okUrl
         
        print UrlNews
 
        # 查找分析链接里面的正文内容，但是由于 163 新闻的格式不是非常统一，所以只能说大部分可以。
        # 整理去掉部分 html 代码，让文本更易于观看。
        n = re.findall(r"<P style=.TEXT-INDENT: 2em.>(.*?)<\/P>",urllib.urlopen(UrlNews).read(),re.M)
        for j in n:
            if len(j)<>0:
                j = j.replace("&nbsp","\n")
                j = j.replace("<STRONG>","\n_____")
                j = j.replace("</STRONG>","_____\n")
                strTxtTmp = strTxtTmp + j + "\n"
                strTxtTmp = re.sub(r"<a href=(.*?)>", r"", strTxtTmp)
                strTxtTmp = re.sub(r"<\/[Aa]>", r"", strTxtTmp)
 
    # 组合链接标题和正文内容    
        strTxtOK = strTxtOK + "\n\n\n===============" + i.split('"')[0] + i.split('"')[1] + "===============\n" + strTxtTmp
        strTxtTmp = ""
        print strTxtOK
 
# 全部分析完成后，写入文件，关闭
f.write(strTitle + "\n\n\n" + strTxtOK)
f.close()


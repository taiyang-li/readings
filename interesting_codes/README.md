# 有趣的小程序
收藏平时积累的一些有趣的小程序

## maifang
### 功能介绍
1. 每天从搜房网爬取所有新房信息，并形成结构化数据, 包括楼盘链接、名称、评分、价格、标签、所在地区、地址、最近一次开盘日期、历史发布、户型、所在楼栋
2. 将当天数据同昨日数据进行比对，得到差异报告，从中可知道哪些楼盘信息更新了，哪些楼盘新增了，方便随时掌握新房动态
3. 将最新楼盘信息持久化到Mongodb中，方便随时查询

### 启动方式
``` bash
cd maifang/bin/
python schedule.sh 
```

### 模块
#### fetcher.Fetcher
根据指定url爬取所有新房信息，支持断点重跑，爬取结果可写入文件，也可写入数据库中

#### house.House
根据输入url爬取某个新房信息，使用BeautifulSoup对网页进行解析

#### writer.Writer
文件写入，将指定msg写入指定路径中

#### mongodb_writer.MongodbWriter
Mongodb写入, 将指定文档写入表中

#### diff_report_generator.DiffReportGenerator
差异报告生成器，读取两天的新房数据，并生成diff数据，写入到markdown文件中

### 可执行文件
#### fetcher.__main__
功能介绍第一步

#### diff_report_generator.__main__
功能介绍第二部

#### save_newhouse.__main__
功能介绍第三部


## raspberrypi
### 功能介绍
1. 使用树莓派自带摄像头，每10秒种拍摄一张照片(yanchi.py)
2. 使用opencv库将多张照片合并成视频，从而实现延迟摄影(convert.cpp)

## games
用pygame实现的两个小游戏，贪吃蛇和俄罗斯方块
### 贪吃蛇
TODO
### 俄罗斯方块
TODO

## zhihu-tool
使用python库zhihu_oauth实现的简单的知乎内容爬取
### me.py
爬取自身账户信息的demo
### other.py
爬去别人账户信息的demo


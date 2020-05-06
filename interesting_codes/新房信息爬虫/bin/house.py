#!/usr/bin/env python
# -*- coding: utf-8 -*

from bs4 import BeautifulSoup
import requests
import time
import re
import json
import logging
from log import log_init

headers = {
        'user-agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36',
        'Cookie': 'XXXX'}

def create_house_by_file(path):
    logging.info('create_house_by_file path:%s' % (path))
    with open(path) as f:
        html = '\n'.join(f.readlines()).decode('utf-8')
    soup = BeautifulSoup(html, 'lxml')
    return House(soup)

def create_house_by_url(url):
    logging.info('create_house_by_url url:%s' % (url))
    try:
        html = requests.get(url, headers=headers)
        html.encoding = 'gb2312'
        soup = BeautifulSoup(html.text, 'lxml')
        return House(soup, url)
    except Exception, e:
        logging.error('create house by url failed, url:%s, error:%s' % (url, str(e)))
        return None

class House(object):
    def __init__(self, soup, url=''):
        self.url = url
        self.soup = soup # 网页的根soup
        self.name = None # 楼盘名称
        self.score = None # 楼盘评分
        self.price = None # 楼盘单价
        self.tags = None # 楼盘标签
        self.region = None # 楼盘所在地区
        self.address = None # 楼盘详细地址
        self.last_kaipan = None # 近期开盘信息
        self.story = None # 楼盘动态
        self.huxing = None # 楼盘户型
        self.loudong = None # 楼盘楼栋信息
        self.history_price = None # 楼盘历史价格走势
        # print soup

    def parse(self):
        logging.info('start parse url:%s' % (self.url))
        self.parse_name()
        self.parse_score()
        self.parse_price()
        self.parse_tags()
        self.parse_region()
        self.parse_address()
        self.parse_last_kaipan()
        self.parse_story()
        self.parse_huxing()
        self.parse_loudong()
        self.parse_history_price()
        logging.info('finish parse url:%s, result:%s' % (self.url, self.to_string()))
        return True

    def parse_name(self):
        try:
            soup_name = self.soup.select('div.information > div.inf_left1 > div.tit > h1 > strong')
            if len(soup_name) == 0:
                soup_name = self.soup.select('h1.lp-name > span')
            self.name = soup_name[0].get_text()
        except Exception, e:
            logging.error('parse name failed: %s, url:%s' % (str(e), self.url))
            return False

        logging.info('parse name success')
        return True

    def parse_score(self):
        try:
            soup_score = self.soup.select('div.information > div.inf_left1 > div.tit > a')
            if len(soup_score) != 0:
                self.score = soup_score[0].get_text().strip().split(u'／')[0]
            else:
                self.score = self.soup.select('h1.lp-name > em > strong')[0].get_text()
        except Exception, e:
            logging.error(('parse score failed: %s, url:%s') % (str(e), self.url))
            return False

        logging.info('parse score success')
        return True

    def parse_price(self):
        try:
            soup_price = self.soup.select('div.information > div.information_li > div.inf_left > span')
            if len(soup_price) != 0:
                self.price = soup_price[0].get_text()
            else:
                self.price = self.soup.select('div.lp-info > div.l-price > strong')[0].get_text()
        except Exception, e:
            logging.error(('parse price failed: %s, url:%s') % (str(e), self.url))
            return False

        logging.info('parse price success')
        return True

    def parse_tags(self):
        try:
            soup_tags = self.soup.select('div.information > div.information_li > div.biaoqian1 > a')
            if len(soup_tags) == 0:
                soup_tags = self.soup.select('div.lp-info > div.lp-type > em.span_name')
            self.tags = []
            for item in soup_tags:
                self.tags.append(item.get_text())
        except Exception, e:
            logging.error(('parse tags failed: %s, url:%s') % (str(e), self.url))
            return False

        logging.info('parse tags success')
        return True

    def parse_region(self):
        try:
            self.region = self.soup.select('div.tf > div.breadcrumb > div.br_left > div > ul > li > a')[2].get_text()
        except Exception, e:
            logging.error(('parse region failed: %s, url:%s') % (str(e), self.url))
            return False

        logging.info('parse region success')
        return True

    def parse_address(self):
        try:
            soup_address = self.soup.select('div.information > div.information_li > div.inf_left > span')
            if len(soup_address) >= 2:
                self.address = soup_address[1].get_text()
            else:
                self.address = self.soup.select('div.lp-info > div.lp-type > span > i')[0].get_text()
                print self.address
        except Exception, e:
            logging.error(('parse address failed: %s, url:%s') % (str(e), self.url))
            return False

        logging.info('parse address success')
        return True

    def parse_last_kaipan(self):
        try:
            self.last_kaipan = self.soup.select('div.information > div.information_li > div.inf_left > a.kaipan')[0].get_text()
        except Exception, e:
            # logging.error(('parse last_kaipan failed: %s, url:%s') % (str(e), self.url))
            self.last_kaipan = None
            return False

        logging.info('parse last_kaipan success')
        return True

    def parse_story(self):
        try:
            soup_story = self.soup.select('div.lp_information_box > div > div.wai > .dldt')
            self.story = []
            for item in soup_story:
                title = item.select('dt > h2 > a.tit')[0].get_text()
                content = item.select('dd > p > a')[0].get_text().split('\n')[0]
                self.story.append({})
                self.story[-1]['title'] = title
                self.story[-1]['content'] = content
        except Exception, e:
            logging.error(('parse story failed: %s, url:%s') % (str(e), self.url))
            return False

        logging.info('parse story success')
        return True

    def parse_huxing(self):
        try:
            soup_huxing = self.soup.select('div.huxing dl.nob')
            self.huxing = []
            for item in soup_huxing:
                soup_a = item.select('dt > a')
                picurl = soup_a[0]['href']
                desc = soup_a[0]['alt'].strip()
                status = soup_a[1].select('div')[0].get_text().strip()
                soup_score = item.select('dd > p:nth-of-type(1) > span')
                score = None if len(soup_score) == 0 else soup_score[0].get_text()

                self.huxing.append({})
                self.huxing[-1]['picurl'] = picurl
                self.huxing[-1]['desc'] = desc
                self.huxing[-1]['status'] = status
                self.huxing[-1]['score'] = score
        except Exception, e:
            logging.error(('parse huxing failed: %s, url:%s') % (str(e), self.url))
            return False

        logging.info('parse huxing success')
        return True

    def parse_loudong(self):
        try:
            soup_loudong = self.soup.select('div.bd-wrapper > div > div.maphsbs')
            self.loudong = []
            for item in soup_loudong:
                version = item['title']
                name = item.select('a > span')[0].get_text()
                status = item.select('a > b')[0].get_text()
                self.loudong.append({})
                self.loudong[-1]['name'] = name
                self.loudong[-1]['version'] = version
                self.loudong[-1]['status'] = status
        except Exception, e:
            logging.error(('parse loudong failed: %s, url:%s') % (str(e), self.url))
            return False

        logging.info('parse loudong success')
        return True

    def parse_history_price(self):
        try:
            soup_exp = self.soup.select('body > div.tf > div.firstbox > div.fjzs > script')
            if len(soup_exp) == 0:
                soup_exp = self.soup.select('div.fjzs > script:nth-of-type(2)')
            exp = soup_exp[0].get_text().strip()

            self.history_price = []
            pattern = re.compile(r'^var \w+\s+=\s+(.*);$')
            match = re.search(pattern, exp)
            if match:
                price_data = json.loads(match.group(1))
                for item in price_data['series']:
                    if item['datatype'] == 'house':
                        # print item['data']
                        for x in item['data']:
                            date = x[0]
                            price = x[1]
                            self.history_price.append({})
                            self.history_price[-1]['date'] = date
                            self.history_price[-1]['price'] = price
                        break
        except Exception, e:
            logging.error(('parse history price failed: %s, url:%s') % (str(e), self.url))
            return False

        logging.info('parse history price success')
        return True

    def to_string(self):
        houseinfo = {}
        houseinfo['url'] = self.url
        houseinfo['name'] = self.name
        houseinfo['score'] = self.score
        houseinfo['price'] = self.price
        houseinfo['tags'] = self.tags
        houseinfo['region'] = self.region
        houseinfo['address'] = self.address
        houseinfo['last_kaipan'] = self.last_kaipan
        houseinfo['story'] = self.story
        houseinfo['huxing'] = self.huxing
        houseinfo['loudong'] = self.loudong
        return json.dumps(houseinfo, ensure_ascii=False)

if __name__ == '__main__':
    log_init('house', '../log')
    house = create_house_by_file('/Users/liyang83/Desktop/work/code/maifang/bin/1.html')
    house.parse()



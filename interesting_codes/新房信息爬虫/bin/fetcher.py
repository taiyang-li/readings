#!/usr/bin/env python
# -*- coding: utf-8 -*

from bs4 import BeautifulSoup
import requests
import time
import random
import re
import json
import logging
from log import log_init
from house import headers, House, create_house_by_file, create_house_by_url
from writer import Writer

class Fetcher(object):
    def __init__(self, url='http://newhouse.hz.fang.com/house/s/',
                 checkpoint_path='../conf/checkpoint.txt',
                 writer=Writer('../data/newhouse')):
        self.url = url
        self.checkpoint_path = checkpoint_path
        self.page_num = None
        self.curr_page = None # 从1开始数
        self.curr_item = None # 从0开始数
        self.writer = writer

    def load_checkpoint(self):
        try:
            with open(self.checkpoint_path) as f:
                line = f.readline().strip()
                values = line.split('\t')
                if len(values) != 2:
                    raise Exception('wrong format of checkpoint')

                curr_page = int(values[0])
                curr_item = int(values[1])
        except Exception, e:
            logging.warning('load checkpoint error:%s' % (str(e)))
            curr_page = 1
            curr_item = 0
        logging.info('load checkpoint page:%d item:%d' % (curr_page, curr_item))
        return (curr_page, curr_item)

    def save_checkpoint(self, checkpoint):
        with open(self.checkpoint_path, 'w') as f:
            f.write('%d\t%d' % (checkpoint[0], checkpoint[1]))
        logging.info('save checkpoint page:%d item:%d' % (checkpoint[0], checkpoint[1]))

    def update_checkpoint(self, item_num):
        if self.curr_item + 1 < item_num:
            self.curr_item += 1
        else:
            self.curr_page += 1
            self.curr_item = 0
        logging.info('update checkpoint page:%d item:%d' % (self.curr_page, self.curr_item))

    def fetch(self):
        self.curr_page, self.curr_item = self.load_checkpoint()
        while self.page_num is None or self.curr_page <= self.page_num:
            ret = self.fetch_one_page()
            if not ret:
                return False
        return True

    def fetch_one_page(self):
        curr_url = self.url if self.curr_page == 1 else ('%sb9%d/') % (self.url, self.curr_page)
        logging.info('start fetch one page, curr_page: %d, url:%s' % (self.curr_page, curr_url))

        html = requests.get(curr_url, headers=headers)
        html.encoding = 'gb2312'
        soup = BeautifulSoup(html.text, 'lxml')

        # 获取总页数
        if self.page_num is None:
            page_num = soup.select('div.otherpage > span')[-1].get_text()
            pattern = re.compile(ur'(\d+)/(\d+)')
            match = re.search(pattern, page_num)
            if match:
                self.page_num = int(match.group(2))
            else:
                logging.error('parse page num failed')
                return False
            logging.info('parse page num success, page_num:%d' % (self.page_num))

        # 获取该业上所有楼盘子链
        soup_house_list = soup.select('div#newhouse_loupai_list div.nlcd_name > a')
        for i, soup_house in enumerate(soup_house_list):
            if i < self.curr_item:
                logging.info('skip page:%d, item:%d' % (self.curr_page, i))
                continue

            house_url = soup_house['href']
            logging.info('house url:%s' % (house_url))
            time.sleep(random.randint(8, 12))
            house = create_house_by_url(house_url)
            if house:
                house.parse()
                self.writer.write(house.to_string())

            # 更新断点
            self.update_checkpoint(len(soup_house_list))
            self.save_checkpoint((self.curr_page, self.curr_item))

        return True

if __name__ == '__main__':
    log_init('fetcher', '../log')
    fetcher = Fetcher()
    fetcher.fetch()



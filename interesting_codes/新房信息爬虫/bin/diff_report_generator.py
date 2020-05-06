#!/usr/bin/env python
# coding: utf-8

import sys
import os
import logging
import json
from time import localtime, strftime, time
from log import log_init

class DiffReportGenerator(object):
    def __init__(self, old_path, new_path, output_path):
        self.old_path = old_path
        self.new_path = new_path
        self.output_path = output_path
        self.old_houses = {}
        self.new_houses = {}
        self.delete_houses = {}
        self.update_houses = {}
        self.insert_houses = {}
        logging.info('old_path:%s new_path:%s output_path:%s' % (self.old_path, self.new_path, self.output_path))

    def generate(self):
        return self.load() and self.diff() and self.save()

    def load(self):
        if not os.path.exists(self.old_path) or not os.path.exists(self.new_path):
            logging.error('path %s and %s not exists' % (self.old_path, self.new_path))
            return False

        self.old_houses = self.load_houses(self.old_path)
        self.new_houses = self.load_houses(self.new_path)
        logging.info('load done')
        return True

    def load_houses(self, path):
        ret = {}
        with open(path) as f:
            for line in f:
                line = line.strip()
                try:
                    house = json.loads(line)
                    url = house['url']
                    ret[url] = house
                except Exception, e:
                    logging.error('load json failed, json:%s' % (line))
        logging.info('load path:%s done, size:%d' %(path, len(ret)))
        return ret

    def diff(self):
        old_urls = set(self.old_houses.keys())
        new_urls = set(self.new_houses.keys())
        delete_urls = old_urls - new_urls
        insert_urls = new_urls - old_urls
        common_urls = old_urls & new_urls

        # delete
        for url in delete_urls:
            self.delete_houses[url] = self.old_houses[url]

        # insert
        for url in insert_urls:
            self.insert_houses[url] = self.new_houses[url]

        # common
        for url in common_urls:
            old_house = self.old_houses[url]
            new_house = self.new_houses[url]
            if old_house == new_house:
                continue

            self.update_houses[url] = {}
            delete_keys = set(old_house.keys()) - set(new_house.keys())
            insert_keys = set(new_house.keys()) - set(old_house.keys())
            common_keys = set(new_house.keys()) & set(old_house.keys())
            for key in delete_keys:
                self.update_houses[url][key] = {}
                self.update_houses[url][key]['old'] = old_house[key]
                self.update_houses[url][key]['new'] = None

            for key in insert_keys:
                self.update_houses[url][key] = {}
                self.update_houses[url][key]['old'] = None
                self.update_houses[url][key]['new'] = new_house[key]

            for key in common_keys:
                if old_house[key] == new_house[key]:
                    continue
                self.update_houses[url][key] = {}
                self.update_houses[url][key]['old'] = old_house[key]
                self.update_houses[url][key]['new'] = new_house[key]
            self.update_houses[url]['total'] = new_house
        logging.info('diff done, del:%d add:%d update:%d' % (len(self.delete_houses), len(self.insert_houses), len(self.update_houses)))
        return True

    def save(self):
        with open(self.output_path, 'w') as f:
            f.write('# 杭州新房差异比对报告 %s vs %s\n' % (os.path.basename(self.old_path).split('.')[-1], os.path.basename(self.new_path).split('.')[-1]))

            # insert
            f.write('## 以下楼盘刚上线\n')
            for url,house in self.insert_houses.items():
                name = house['name']
                f.write('### %s\n' % (name.encode('utf-8')))
                f.write('\n')
                f.write('字段 | 值\n')
                f.write('--- | ---\n')
                for k,v in house.items():
                    f.write(k)
                    f.write(' | ')
                    f.write(json.dumps(v, ensure_ascii=False).encode('utf-8'))
                    f.write('\n')
                f.write('\n')

            # update
            f.write('## 以下楼盘已更新状态\n')
            for url,house in self.update_houses.items():
                name = house['total']['name']
                f.write('### %s\n' % (name.encode('utf-8')))
                f.write('基本信息:\n')
                f.write('```\n')
                f.write(json.dumps(house['total'], ensure_ascii=False).encode('utf-8'))
                f.write('```\n')
                f.write('\n')
                f.write('字段 | 旧值 | 新值\n')
                f.write('--- | --- | ---\n')
                for k,v in house.items():
                    if k == 'total':
                        continue
                    f.write(k)
                    f.write(' | ')
                    f.write(json.dumps(v['old'], ensure_ascii=False).encode('utf-8'))
                    f.write(' | ')
                    f.write(json.dumps(v['new'], ensure_ascii=False).encode('utf-8'))
                    f.write('\n')
                f.write('\n')

            # delete
            f.write('## 以下楼盘已下线\n')
            for url,house in self.delete_houses.items():
                name = house['name']
                f.write('### %s\n' % (name.encode('utf-8')))
                f.write('\n')
                f.write('字段 | 值\n')
                f.write('--- | ---\n')
                for k,v in house.items():
                    f.write(k)
                    f.write(' | ')
                    f.write(json.dumps(v, ensure_ascii=False).encode('utf-8'))
                    f.write('\n')
                f.write('\n')

        logging.info('save done')
        return True

if __name__ == '__main__':
    log_init('diff', '../log')
    today = strftime("%Y%m%d", localtime())
    yesterday = strftime("%Y%m%d", localtime(time() - 86400))
    old_path = '../data/newhouse.%s' % (today)
    new_path = '../data/newhouse.%s' % (yesterday)
    output_path = '../data/diff.%s.%s.md' % (yesterday, today)
    gen = DiffReportGenerator(old_path, new_path, output_path)
    gen.generate()

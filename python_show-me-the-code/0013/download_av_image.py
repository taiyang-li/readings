#!/usr/bin/env python 
# -*- coding: utf-8 -*

from bs4 import BeautifulSoup 
import urllib
import urllib2
import sys
import os

def save_img(img_url,file_name,file_path='./output'):
    try:
        if not os.path.exists(file_path):
            os.makedirs(file_path)
        file_suffix = os.path.splitext(img_url)[1]
        if file_suffix == '.jpg':
            filename = '{}{}{}{}'.format(file_path,os.sep,file_name,file_suffix)
            urllib.urlretrieve(img_url,filename=filename)
    except IOError as e:
        print e
    except Exception as e:
        print e

def download_av_image(url):
    proto, rest = urllib.splittype(url)
    domain = urllib.splithost(rest)[0]

    html = urllib2.urlopen(url).read()
    post_list = BeautifulSoup(html).findAll('div', class_ = 'd_post_content_main')
    image_id = 0
    for post in post_list:
        image_list = post.findAll('img');
        for image in image_list:
            if image.get('src') is None:
                continue
            save_img(image['src'], str(image_id))
            print "download %d finish" % (image_id)
            image_id += 1

download_av_image('http://tieba.baidu.com/p/2166231880')



#!/usr/bin/env python
# coding: utf-8

from collections import namedtuple
from PIL import Image
import os

data_in_path = './data_in/'
p5_data_out_path = './p5_data_out/'
p6_data_out_path = './p6_data_out/'
p6p_data_out_path = './p6p_data_out/'

ScreenSize = namedtuple('ScreenSize', ['width', 'height'])
iphone5_size = ScreenSize(640, 1136)
iphone6_size = ScreenSize(750, 1334)
iphone6p_size = ScreenSize(1080, 1920)

def resize_image(data_in_path, data_out_path, name, imgtype, target_size):
    im = Image.open(data_in_path + name)
    rate = max(im.size[0]/float(target_size.width) if im.size[0] > target_size.width else 0, im.size[1]/float(target_size.height) if im.size[1] > target_size.height else 0)
    if rate:
        im.thumbnail((im.size[0]/rate, im.size[1]/rate))

    imgtype = 'jpeg' if imgtype == '.jpg' else 'png'
    im.save(data_out_path + name, imgtype)

def run(data_in_path, data_out_path, target_size):
    assert isinstance(target_size, ScreenSize)
    for name in os.listdir(data_in_path):
        suffix = os.path.splitext(name)[1]
        if suffix == '.jpg' or suffix == '.png':
            resize_image(data_in_path, data_out_path, name, suffix, target_size)

if __name__ == '__main__':
    run(data_in_path, p5_data_out_path, iphone5_size)
    run(data_in_path, p6_data_out_path, iphone6_size)
    run(data_in_path, p6p_data_out_path, iphone6p_size)

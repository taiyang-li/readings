#!/usr/bin/env python
# coding: utf-8

from PIL import Image
import os

data_in_path = './data_in/'
data_out_path = './data_out/'

def resize_image(data_in_path, data_out_path, name, imgtype):
    im = Image.open(data_in_path + name)
    rate = max(im.size[0]/640.0 if im.size[0] > 640 else 0, im.size[1]/1136.0 if im.size[1] > 1136 else 0)
    if rate:
        im.thumbnail((im.size[0]/rate, im.size[1]/rate))

    imgtype = 'jpeg' if imgtype == '.jpg' else 'png'
    im.save(data_out_path + name, imgtype)

def run():
    for name in os.listdir(data_in_path):
        suffix = os.path.splitext(name)[1]
        if suffix == '.jpg' or suffix == '.png':
            resize_image(data_in_path, data_out_path, name, suffix)

if __name__ == '__main__':
    run()

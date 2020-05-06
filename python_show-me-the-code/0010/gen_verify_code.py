#!/usr/bin/env python 
# -*- coding: utf-8 -*

import random
from PIL import Image, ImageDraw, ImageFont, ImageFilter
import string

def get_random_char():
    return random.choice(string.letters)

def get_random_color():
    return (random.randint(30, 100), random.randint(30, 100), random.randint(30, 100))

def get_verify_code(path):
    width = 240
    height = 60

    image = Image.new('RGB', (width, height), (180,180,180))
    font = ImageFont.truetype('Skia.ttf', 40)
    draw = ImageDraw.Draw(image)
    for t in range(4):
        code = get_random_char()
        color = get_random_color()
        draw.text((60 * t + 10, 0), code, font=font, fill=color)

    for _ in range(random.randint(1500,3000)):
        draw.point((random.randint(0,width), random.randint(0,height)), fill=get_random_color())

    image = image.filter(ImageFilter.BLUR)
    image.save(path + '.jpg', 'jpeg');

get_verify_code('./1')



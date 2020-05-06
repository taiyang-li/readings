#!/usr/bin/env python
# -*- coding: utf-8 -*

from PIL import  Image,ImageDraw,ImageFont

def addNum(nub,filepath):
    img = Image.open(filepath)

    draw = ImageDraw.Draw(img)
    width, height = img.size
    fontSize = height/4

    myFont = ImageFont.truetype('Skia.ttf', fontSize)
    # myFont = ImageFont.load_default()

    draw.text((width-fontSize,0),nub,(256,0,0),font=myFont)
    del draw
    img.save('res.png')

if __name__ == '__main__':
    addNum('19','test.png')


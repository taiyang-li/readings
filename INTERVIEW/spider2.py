import os
import sys
import re
import urllib
 
VANCAL_ITEM = re.compile(r'http://vt.vancl.com/item/(\d+).*', re.I)
ITEM_PIC = re.compile(r'(http://images.vancl.com/product/.*?/small/.*?\.jpg)', re.I)
 
def download(dir, url):
 
    global VANCAL_ITEM, ITEM_PIC
     
    if not os.path.isdir(dir):
        os.mkdir(dir)
     
    html = urllib.urlopen(url).read()
    items = [item for item in VANCAL_ITEM.findall(html)]
    for idx, item in enumerate(items):
        item_url = 'http://vt.vancl.com/item/' + item + '.html'
        print idx, ": ", item_url
 
        dl_dir = dir + item + '\\'
        try:
            os.makedirs(dl_dir)
        except:
            pass
        item_html = urllib.urlopen(item_url).read()
        item_pics = [item for item in ITEM_PIC.findall(item_html)]
        for sidx, sitem in enumerate(item_pics):
            tmp = sitem.replace("small", "mid")
            name = tmp.split('/')[-1]
            dl_name = os.path.join(dl_dir, name)
            urllib.urlretrieve(tmp, dl_name)
    return
     
def main():
    dir = 'd:\\img\\'
    ss = 'http://vt.vancl.com/list/women/'
    ed = '/view=1'
    for idx in range(10):
        download(dir, ss + str(idx + 1) + ed)
         
if __name__ == '__main__':
    main()

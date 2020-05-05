#!/bin/bash
# sed»ù±¾ÓÃ·¨

# sed "s///" Ìæ»»
echo  "hello wolrd" | sed "s/hello/goodbye/"
touch 1.txt
cat>1.txt<<EOF
hello world
EOF

# sed -i Ìæ»»ÎÄ¼þÄÚÈÝ
sed -i 's/hello/goodbye/' 1.txt

# sed 's///g' Ìæ»»ËùÓÐÆ¥ÅäÄÚÈÝ
echo "thisthisthisthis" | sed 's/this/THIS/g'

# sed 's///ng' ´ÓµÚn´¦Æ¥Åä¿ªÊ¼Ìæ»»
echo "thisthisthisthis" | sed 's/this/THIS/2g'

# sed '//d' É¾³ýÆ¥ÅäÐÐ
cat diff.sh | sed '/^$/d' 

# Æ¥Åä×Ö·û´®±ê¼Ç
echo this is an example | sed 's/\w\+/[&]/g'

# ²¶×½×Ö·û´®
echo "this is a digit 7 in a numbger" | sed 's/digit \([0-9]\)/\1/'

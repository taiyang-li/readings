#!/bin/bash

# set -x
sed -i bak 's/\|/ /g' $1
# cat $1
sed -i bak 's/\+//g' $1
# cat $1
sed -i bak 's/-\{2,\}//g' $1
# cat $1
sed -i bak '/^$/d' $1
# cat $1
sed -i bak 's/^ \{1,\}//g' $1
# cat $1
sed -i bak 's/ \{1,\}$//g' $1
# cat $1
sed -i bak 's/ \{1,\}/,/g' $1
# cat $1
# set +x

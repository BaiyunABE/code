#!/bin/bash

a=(A B "C" D)

echo 'a[0]='${a[0]}
echo 'a[1]='${a[1]}
echo 'a[2]='${a[2]}
echo 'a[3]='${a[3]}
echo 'a='${a[*]}
echo 'n='${#a[*]}

declare -A site
site["google"]="www.google.com"
site["runoob"]="www.runoob.com"
site["taobao"]="www.taobao.com"
echo ${site["runoob"]}
echo 'site='${site[*]}
echo 'n='${#site[*]}
echo 'keys='${!site[*]}

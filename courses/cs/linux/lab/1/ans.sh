#!/bin/bash

wget $1 &> /dev/null

file=$(echo $1 | sed "s/.*\(history[0-9]*\.html\)/\1/")

title=$(cat $file | tr -d '\n' | sed 's/.*<title>\(.*\)<\/title>.*/\1/')

city=$(echo $title | sed 's/\(.*\)市.*/\1/')

year=$(echo $title | sed 's/.*市\([0-9]*\).*/\1/')

action=$(printf '{printf \"%s,%s-%%s,%%s,%%s,%%s,%%s\\n\", $1, $3, $4, $5, $7}' $city $year)

cat $file | tr -d '\n ' | sed -f sed.cmd | tail -n +2 | awk "$action"
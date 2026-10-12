#!/bin/bash
rm history*.html &> /dev/null
./ans.sh www.tianqi24.com/beijing/history202307.html
echo ""
./ans.sh www.tianqi24.com/kaifeng/history202011.html
rm history*.html &> /dev/null
#!/bin/bash
echo "启动 32 个并发进程：0~31号分片"
for i in {0..31}
do
    python3 main.py $i & # > log_$i.txt 2>&1 &
    # echo "启动 $i 号进程，日志: log_$i.txt"
done
echo
echo "所有后台进程已启动！"
# echo "实时查看某一片：tail -f log_0.txt"
# echo "查看所有完成情况：grep '完成' log_*.txt"

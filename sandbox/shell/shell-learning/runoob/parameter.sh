#!/bin/bash
echo 'filename: '$0
echo 'param 1: '$1
echo 'num of params: '$#
echo 'all params: '$*
echo 'all params: '$@
echo 'pid: '$$

echo '-- $* demo --'
for i in "$*"; do
	echo $i
done

echo '-- $@ demo --'
for i in "$@"; do
	echo $i
done

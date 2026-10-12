#!/bin/bash

a=10
b=20

val=`expr $a + $b`
echo "a + b = $val"

val=`expr $a - $b`
echo "a - b = $val"

val=`expr $a \* $b`
echo "a * b = $val"

val=`expr $a / $b`
echo "a / b = $val"

val=`expr $a % $b`
echo "a % b = $val"

if [ $a -eq $b ] then
	echo "a == b"
fi

if [ $a -ne $b ] then
	echo "a != b"
fi

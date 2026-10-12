#!/usr/bin/bash
cc main.c
{
  echo "9"
  echo "1 2 3 4 5 6 7 8 9"
} | ./a.out
rm a.out

#!/usr/bin/python3

a = [0,6,4,7,2,5,1,8,9,3]
n = len(a)
b = [False] * n


def putc(c):
    print(c, end='')


for i in range(1, n):
    if b[i] == True:
        continue

    putc('(')
    j = i

    while True:
        putc(j)
        b[j] = True
        j = a[j]

        if j == i:
            break
        
    putc(')')

putc('\n')

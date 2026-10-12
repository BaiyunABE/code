#!/usr/bin/python3
def f():
    n = 0
    for i in list(input()):
        if i == 'a':
            n += 1
        elif i == 'b' and n != 0:
            n -= 1
        else:
            return 'Bad'

    return 'Good' if n == 0 else 'Bad'


print(f())

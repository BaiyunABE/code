#!/usr/bin/python3

def f(s: str):
    new = list(s)
    old = []
    while "".join(old) != "".join(new):
        old = []
        for i in new:
            if i != '\0':
                old.append(i)
        new = old.copy()
        i = 0
        while i != len(new):
            if i != len(new) - 1 and new[i] == 'o' and new[i + 1] == 'o':
                new[i] = 'O'
                new[i + 1] = '\0'
                i += 2
                break
            elif i != len(new) - 1 and new[i] == 'O' and new[i + 1] == 'O':
                new[i] = '\0'
                new[i + 1] = '\0'
                i += 2
                break
            else:
                i += 1
    return "".join(new)

def g(s: str):
    new = list(s)
    old = []
    while old != new:
        old = new
        new = []
        i = 0
        while i != len(old):
            if i != len(old) - 1 and old[i] == 'o' and old[i + 1] == 'o':
                new.append('O')
                i += 2
            elif i != len(old) - 1 and old[i] == 'O' and old[i + 1] == 'O':
                i += 2
            else:
                new.append(old[i])
                i += 1
    return "".join(new)

a = input()
print(f(a))
print(g(a))
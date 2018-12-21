from random import *

outp = ""

def gen(n, m):
    n, m = int(n), int(m)
    assert m >= n - 1
    out = "%d %d\n" % (n, m)
    idx = [i + 1 for i in range(n)]
    shuffle(idx)
    for i in range(1, n):
        out += "%d %d\n" % (idx[i], idx[randint(0, i-1)])
    for i in range(m - n + 1):
        u, v = randint(1, n), randint(1, n)
        while u == v:
            u, v = randint(1, n), randint(1, n)
        out += "%d %d\n" % (idx[u-1], idx[v-1])
    return out

def spc(n):
    n = int(n)
    m = (n - 1) * 2
    out = "%d %d\n" % (n, m)
    for i in range(1, n):
        out += "%d %d\n" % (i, i + 1)
        out += "%d %d\n" % (i, i + 1)
    return out

def sml():
    return "5 7\n1 4\n1 2\n2 3\n2 3\n3 4\n4 5\n4 5\n"

def Gen(id):
    global outp
    if id ==  0: outp += sml()
    if id ==  1: outp += gen( 11,    20)
    if id ==  2: outp += gen( 12,    29)
    if id ==  3: outp += gen( 21,    51)
    if id ==  4: outp += gen(1e2,   1e2)
    if id ==  5: outp += gen(5e2,   1e3)
    if id ==  6: outp += gen(5e2,   2e3)
    if id ==  7: outp += gen(5e2,   5e3)
    if id ==  8: outp += gen(1e3,   1e3)
    if id ==  9: outp += gen(1e3,   2e3)
    if id == 10: outp += gen(6e3,   7e3)
    if id == 11: outp += gen(6e3,   1e4)
    if id == 12: outp += gen(1e4, 1.5e4)
    if id == 13: outp += gen(1e4,   2e4)
    if id == 14: outp += spc(1e4)
    if id == 15: outp += gen(2e4, 2e4-1)
    if id == 16: outp += gen(2e4, 3.5e4)
    if id == 17: outp += gen(1e5, 1.5e5)
    if id == 18: outp += gen(1e5,   2e5)
    if id == 19: outp += spc(1e5)

T = 20
outp += "%d\n" % (T)

for id in range(0, T):
    print("Generating testcase #%d" % (id))
    Gen(id)

print(outp, file=open("std.in", "w"))

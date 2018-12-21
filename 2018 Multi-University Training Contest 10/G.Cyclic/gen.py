from random import *

T = 20
n = int(1e5)
outp = "%d\n" % (T)
for i in range(T-1):
    outp += "%d\n" % (randint(1, n))
outp += "%d\n" % (n)
print(outp, file=open("std.in", "w"))

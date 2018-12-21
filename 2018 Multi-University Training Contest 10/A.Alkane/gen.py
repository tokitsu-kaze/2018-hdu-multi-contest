from random import *

t = 100000
outp = "%d\n" % (t)
for i in range(t):
    outp += "%d\n" % (i + 1)
print(outp, file=open("std.in", "w"))

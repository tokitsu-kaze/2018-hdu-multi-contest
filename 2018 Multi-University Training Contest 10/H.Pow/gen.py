from random import *

t = 20
outp = "%d\n" % (t)
outp += "0\n"
for i in range(t - 2):
    outp += "%d\n" % (randint(0, 1000))
outp += "1000\n"
print(outp, file=open("std.in", "w"))
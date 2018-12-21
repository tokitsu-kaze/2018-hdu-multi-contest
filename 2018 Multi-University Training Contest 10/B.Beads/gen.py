from random import *

Ns = [106858629141264000,
      112201560598327200,
      149602080797769600,
      224403121196654400,
      299204161595539200,
      374005201994424000,
      448806242393308800,
      673209363589963200,
      748010403988848000,
      897612484786617600,
]

def gen(noddn, noddm):
    n = choice(Ns)
    while not noddn and n % 2 == 0:
        n //= 2
    m = choice(Ns)
    while not noddm and m % 2 == 0:
        m //= 2

    assert n > 2 and m > 1
    assert n % 998244353 != 0
    assert m % 998244353 != 0

    return "%d %d\n" % (n, m)

t = 20
outp = "%d\n" % (t)
outp += "957564459713286289 66666666666666\n"
outp += "957564459713286289 978438233\n"
# outp += gen(False, False)
# outp += gen( True, False)
# outp += gen(False, False)
# outp += gen(False,  True)
# outp += gen( True, False)
outp += gen( True,  True)
outp += gen(False, False)
outp += gen(False,  True)
outp += gen( True, False)
outp += gen( True,  True)
outp += gen(False, False)
outp += gen(False, False)
outp += gen(False,  True)
outp += gen(False,  True)
outp += gen(False,  True)
outp += gen( True, False)
outp += gen( True, False)
outp += gen( True,  True)
outp += gen( True,  True)
outp += gen( True,  True)
outp += "186409786110172186 666\n"
outp += "186409786110172186 23333333333333\n"
outp += "186409786110172186 20000327\n"

print(outp, file=open("std.in", "w"))

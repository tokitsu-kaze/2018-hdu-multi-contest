// Copyright (C) 2017 __debug.

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; version 3

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; If not, see <http://www.gnu.org/licenses/>.


#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

#define x first
#define y second
#define MP std::make_pair
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#ifdef __linux__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

using std::pair;
using std::vector;
using std::string;

typedef long long LL;
typedef pair<int, int> Pii;

const int oo = 0x3f3f3f3f;

template<typename T> inline bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
template<typename T> inline bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
// EOT

#ifndef __linux__
#define rand() (rand() << 15 ^ rand())
#endif

const int MOD = 998244353;

LL mul(LL base, LL exp, LL mod)
{
    LL ret = 0;
    for (; exp; exp >>= 1) {
        if (exp & 1)
            (ret += base) %= mod;
        (base += base) %= mod;
    }
    return ret;
}

LL fpm(LL base, LL exp, LL mod)
{
    LL ret = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1)
            ret = mul(ret, base, mod);
        base = mul(base, base, mod);
    }
    return ret;
}

LL fpm(LL base, LL exp)
{
    LL ret = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1)
            (ret *= base) %= MOD;
        (base *= base) %= MOD;
    }
    return ret;
}

bool isprime(LL x)
{
    const int SIZE = 12;
    const int PRIMES[SIZE] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    if (x == 2) return true;
    if (x == 1 || !(x & 1)) return false;

    LL k = x - 1, t = 0;
    for (; !(k & 1); k >>= 1) ++t;
    for (int i = 0; i < SIZE && PRIMES[i] < x; ++i) {
        LL g = fpm(PRIMES[i], k, x);
        for (int j = 0; j < t; ++j) {
            LL g0 = mul(g, g, x);
            if (g0 == 1 && g != 1 && g != x - 1) return false;
            g = g0;
        }
        if (g != 1) return false;
    }
    return true;
}

vector<LL> pf;
LL totfactors, factors[75], fcnt[75];

#define F(t) ((mul(t, t, x) + c) % x)

void pollardRho(LL x)
{
    if (isprime(x)) {
        pf.push_back(x);
        return;
    }
    for (;;) {
        LL c = rand() % (x - 1) + 1;
        LL p = rand() % x, q = F(p);
        while (p != q) {
            LL d = std::__gcd(x, std::abs(p - q));
            if (d != 1) {
                pollardRho(d);
                pollardRho(x / d);
                return;
            }
            p = F(p); q = F(F(q));
        }
    }
}

void getPrimeFactors(LL x)
{
    pf.clear();
    pollardRho(x);
    std::sort(ALL(pf));
    assert(SZ(pf) >= 1);

    totfactors = 0;
    factors[totfactors] = pf[0];
    fcnt[totfactors] = 1;
    for (int i = 1; i < SZ(pf); ++i) {
        if (pf[i] == factors[totfactors])
            ++fcnt[totfactors];
        else {
            factors[++totfactors] = pf[i];
            fcnt[totfactors] = 1;
        }
    }
    ++totfactors;

    // for (int i = 0; i < totfactors; ++i) {
    //     printf("(%lld,%lld),", factors[i], fcnt[i]);
    // }
    // puts("");
}

LL N, M;
LL sum;

void dfs(int cur, LL x, LL phi)
{
    if (cur == totfactors) {
        (sum += (std::__gcd(M, x) % MOD) * (phi % MOD) % MOD * fpm(M % MOD, N / x) % MOD) %= MOD;
        return;
    }
    LL y = factors[cur];
    dfs(cur + 1, x, phi);
    x *= y; phi *= y - 1;
    dfs(cur + 1, x, phi);
    for (int i = 2; i <= fcnt[cur]; ++i) {
        x *= y; phi *= y;
        dfs(cur + 1, x, phi);
    }
}

void solve()
{
    assert(N >= 3 && M >= 2);
    assert(N % MOD != 0 && M % MOD != 0);

    sum = 0;
    if (N & 1) {
        (sum += std::__gcd(M, 1ll) * (N % MOD) * fpm(M % MOD, N / 2 + 1) % MOD) %= MOD;
    } else {
        (sum += std::__gcd(M, 1ll) * (N / 2 % MOD) * fpm(M % MOD, N / 2 + 1) % MOD) %= MOD;
        (sum += std::__gcd(M, 2ll) * (N / 2 % MOD) * fpm(M % MOD, N / 2)) %= MOD;
    }

    getPrimeFactors(N);
    dfs(0, 1, 1);

    int ans = sum * fpm(2 * (N % MOD) % MOD * (M % MOD) % MOD, MOD - 2) % MOD;
    printf("%d\n", ans);
}

int main()
{
#ifdef __DEBUG
    freopen("std.in", "r", stdin);
    freopen("std.out", "w", stdout);
#endif
    srand(time(NULL));

    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld", &N, &M);
        solve();
    }

    return 0;
}

// 忆昔花间相见后，只凭纤手，暗抛红豆。
//     -- 欧阳炯《贺明朝·忆昔花间相见后》

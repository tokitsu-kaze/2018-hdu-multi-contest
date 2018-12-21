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

const int MAXN = 1e5 + 5;
const int MOD = 998244353;

int N;
int fac[MAXN], ifac[MAXN];

int fpm(int base, int exp)
{
    int ret = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1)
            ret = (LL)ret * base % MOD;
        base = (LL)base * base % MOD;
    }
    return ret;
}

void prework()
{
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        fac[i] = (LL)fac[i - 1] * i % MOD;
        ifac[i] = fpm(fac[i], MOD - 2);
    }
}

void solve()
{
    int ans = N & 1 ? MOD - 1 : 1;
    for (int k = 0; k < N; ++k) {
        int t = (LL)fac[N] * ifac[k] % MOD * ifac[N - k] % MOD * fac[N - k - 1] % MOD;
        if (k & 1)
            (ans += MOD - t) %= MOD;
        else
            (ans += t) %= MOD;
    }
    printf("%d\n", ans);
}

int main()
{
#ifdef __DEBUG
    freopen("std.in", "r", stdin);
    freopen("std.out", "w", stdout);
#endif

    prework();

    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        solve();
    }

    return 0;
}

// 胡未灭，鬓先秋。泪空流。
//     -- 陆游《诉衷情·当年万里觅封侯》

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

const int MAXN = 103;

int N, P;

inline void mod(int &x) { x = (x >= P ? x - P : x); }

void solve()
{
    static int f[MAXN][MAXN * MAXN], g[MAXN][MAXN * MAXN];

    memset(g, 0, sizeof(g));
    g[0][0] = g[1][0] = 1;
    for (int i = 1; i < N; ++i) {
        memcpy(f, g, sizeof(f));
        memset(g, 0, sizeof(g));
        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k <= i * i; ++k) {
                if (!f[j][k]) continue;
                mod(g[j][k + j] += (LL)(2 * j + 1) * f[j][k] % P);
                if (j) mod(g[j - 1][k + j] += (LL)j * j * f[j][k] % P);
                mod(g[j + 1][k + j] += f[j][k]);
            }
        }
    }

    for (int i = 0; i < N * N; ++i) {
        int cur = i & 1 ? 0 : g[0][i / 2];
        printf("%d%c", cur, " \n"[i == N * N - 1]);
    }
}

int main()
{
#ifdef __DEBUG
    freopen("std.in", "r", stdin);
    freopen("std.out", "w", stdout);
#endif

    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &P);
        solve();
    }

    return 0;
}

// 楼台处处迷芳草，风雨年年怨落花。
//     -- 曾棨《维扬怀古》

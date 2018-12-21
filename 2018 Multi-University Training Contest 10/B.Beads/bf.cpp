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

LL N, M;
std::set<vector<int> > S;
vector<int> cur;
LL ans;

void dfs(int x)
{
    if (x == N) {
        if (S.count(cur)) return;

        vector<int> ori(cur);

        // for (int i = 0; i < N; ++i) {
        //     printf("%d ", ori[i]);
        // }
        // puts("");

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                S.insert(cur);
                std::rotate(cur.begin(), cur.begin() + 1, cur.end());
            }
            for (int j = 0; j < N; ++j) {
                vector<int> vec(N);
                for (int k = 0; k < N; ++k) vec[(j - k + N) % N] = cur[k];
                S.insert(vec);
            }
            for (int k = 0; k < N; ++k) (++cur[k]) %= M;
        }

        ++ans;
        assert(ori == cur);

        return;
    }
    for (int i = 0; i < M; ++i) {
        cur[x] = i;
        dfs(x + 1);
    }
}

void solve()
{
    ans = 0;
    cur.resize(N);
    S.clear();
    dfs(0);
    printf("%lld\n", ans % MOD);
}

int main()
{
    freopen("std.in", "r", stdin);
    freopen("bf.out", "w", stdout);
    srand(time(NULL));

    int T;
    scanf("%d", &T);
    while (T--) {
        DEBUG("left %d\n", T);
        scanf("%lld%lld", &N, &M);
        solve();
    }

    return 0;
}

// 忆昔花间相见后，只凭纤手，暗抛红豆。
//     -- 欧阳炯《贺明朝·忆昔花间相见后》

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

const int MAXN = 1e5 + 5, MAXM = 3e5 + 5;

struct Edge {
    int v, next;
    Edge() { }
    Edge(int v_, int next_): v(v_), next(next_) { }
};

int N, M;
int tote, head[MAXN];
Edge edge[MAXM * 2 + 5];
int SN, SM;

inline void addEdge(int u, int v)
{
    edge[++tote] = Edge(v, head[u]);
    head[u] = tote;
}

void input()
{
    scanf("%d%d", &N, &M);
    SN += N;
    SM += M;
    tote = 1;
    memset(head + 1, 0, sizeof(*head) * N);
    for (int i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        assert(u != v);
        addEdge(u, v);
        addEdge(v, u);
    }
}

int dep[MAXN], size[MAXN], size0[MAXN];
bool ontree[MAXM];
LL val[MAXM];
std::set<LL> S;
std::map<LL, int> T;
LL allsize, tot;

LL Rand() { return (LL)rand() << 31 | rand(); }

LL dfs1(int u, int e)
{
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if ((i >> 1) == e)
            continue;
        if (!dep[v]) {
            dep[v] = dep[u] + 1;
            ontree[i >> 1] = true;
            val[e] ^= dfs1(v, i >> 1);
            size[u] += size[v];
        }
    }
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if (ontree[i >> 1])
            continue;
        if (dep[v] < dep[u]) {
            val[i >> 1] = Rand();
            S.insert(val[i >> 1]);
        }
        val[e] ^= val[i >> 1];
    }
    return val[e];
}

int clear(int u, int e, int forbid)
{
    if (!size0[u])
        return 0;
    if (forbid == u)
        return size0[u];
    size0[u] = 0;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if ((i >> 1) != e && ontree[i >> 1])
            size0[u] += clear(v, i >> 1, forbid);
    }
    return size0[u];
}

int dfs2(int u, int e)
{
    size0[u] = 1;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if ((i >> 1) != e && ontree[i >> 1])
            size0[u] += dfs2(v, i >> 1);
    }
    if (T.find(val[e]) != T.end()) {
        int v = T[val[e]];
        int t = size0[u] - size0[v];
        tot += (allsize - t) * t; allsize -= t;
        clear(u, e, v);
    } else if (S.find(val[e]) != S.end()) {
        int t = size0[u];
        tot += (allsize - t) * t; allsize -= t;
        clear(u, e, 0);
    }
    T[val[e]] = u;
    return size0[u];
}

int dfs3(int u, int e)
{
    size0[u] = 1;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if ((i >> 1) != e && ontree[i >> 1])
            size0[u] += dfs3(v, i >> 1);
    }
    if (val[e] == 0) {
        int t = size0[u];
        tot += (allsize - t) * t; allsize -= t;
        clear(u, e, 0);
    }
    return size0[u];
}

void solve()
{
    LL ans = 0;

    memset(dep + 1, 0, sizeof(*dep) * N);
    memset(val + 1, 0, sizeof(*val) * M);
    memset(ontree + 1, 0, sizeof(*ontree) * M);

    for (int rt = 1; rt <= N; ++rt) {
        if (dep[rt])
            continue;
        S.clear(); S.insert(0);
        T.clear();
        dep[rt] = 1;
        dfs1(rt, 0);

        allsize = size[rt];
        LL totx = allsize * (allsize - 1) / 2;
        allsize = size[rt]; tot = 0; dfs2(rt, 0);
        LL tot2 = tot;
        allsize = size[rt]; tot = 0; dfs3(rt, 0);
        LL tot1 = tot;
        ans += tot1 + (tot2 - tot1) * 2 + (totx - tot2) * 3;
    }

    printf("%lld\n", ans);
}

int main()
{
#ifdef __DEBUG
    freopen("std.in", "r", stdin);
    freopen("std.out", "w", stdout);
#endif
    srand(time(NULL));

    int tt;
    scanf("%d", &tt);
    while (tt--) {
        input();
        solve();
    }

    return 0;
}

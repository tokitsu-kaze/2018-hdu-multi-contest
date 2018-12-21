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
string procStatus()
{
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}
template<typename T> T read(T &x)
{
    int f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        f = (ch == '-' ? -1 : 1);
    for (x = 0; isdigit(ch); ch = getchar())
        x = 10 * x + ch - '0';
    return x *= f;
}
template<typename T> void write(T x)
{
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static char s[20];
    int top = 0;
    for (; x; x /= 10)
        s[++top] = x % 10 + '0';
    while (top)
        putchar(s[top--]);
}
// EOT

const int MAXN = 1e4 + 5, MAXM = 1e5 + 5;

int N, M, Q;

namespace Dinic
{

struct Edge {
    int v, next;
    int cap, rsd;
    Edge() { }
    Edge(int v_, int next_, int cap_): v(v_), next(next_), cap(cap_), rsd(cap_) { }
};

int n, s, t;
int tote, head[MAXN], cur[MAXN];
Edge edge[MAXM];
int dis[MAXN];

inline void addEdge(int u, int v, int cap)
{
    edge[++tote] = Edge(v, head[u], cap);
    head[u] = tote;
}

inline void init()
{
    tote = 1;
    memset(head, 0, sizeof(head));
}

inline void clear()
{
    for (int i = 2; i <= tote; ++i) {
        edge[i].rsd = edge[i].cap;
    }
}

bool bfs()
{
    static int q[MAXN];
    int front = 0, rear = 0;

    memset(dis, +oo, sizeof(dis));
    dis[s] = 0;
    q[rear++] = s;
    while (front != rear) {
        int u = q[front++];
        for (int i = head[u]; i; i = edge[i].next) {
            const Edge &e = edge[i];
            if (e.rsd > 0 && chkmin(dis[e.v], dis[u] + 1))
                q[rear++] = e.v;
        }
    }
    return dis[t] != +oo;
}

int dfs(int u, int rsd)
{
    if (u == t || !rsd)
        return rsd;
    int ret = 0;
    for (int &i = cur[u]; i; i = edge[i].next) {
        Edge &e = edge[i];
        if (e.rsd > 0 && dis[u] + 1 == dis[e.v]) {
            int f = dfs(e.v, std::min(e.rsd, rsd));
            if (f > 0) {
                e.rsd -= f; edge[i^1].rsd += f;
                rsd -= f; ret += f;
                if (!rsd) break;
            }
        }
    }
    return ret;
}

int exec(int s_, int t_)
{
    s = s_; t = t_;
    int ret = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(cur));
        ret += dfs(s, +oo);
    }
    return ret;
}

}

void input()
{
    read(N); read(M);
    if (N >= MAXN) exit(0);
    Dinic::init();
    for (int i = 1; i <= M; ++i) {
        int u, v;
        read(u); read(v);
        assert(u != v);
        Dinic::addEdge(u, v, 1);
        Dinic::addEdge(v, u, 1);
    }
}

int id[MAXN];
vector<Pii> G[MAXN];
int dep[MAXN], fa[MAXN], fw[MAXN];

void dnc(int l, int r)
{
    if (l >= r) return;
    Dinic::clear();
    int s = id[l], t = id[r];
    int f = Dinic::exec(s, t);
    G[s].push_back(MP(t, f));
    G[t].push_back(MP(s, f));

    static int L[MAXN], R[MAXN];
    int totL = 0, totR = 0;
    for (int i = l; i <= r; ++i) (Dinic::dis[id[i]] < +oo ? L[totL++] : R[totR++]) = id[i];
    for (int i = 0; i < totL; ++i) id[l + i] = L[i];
    for (int i = 0; i < totR; ++i) id[l + totL + i] = R[i];

    dnc(l, l + totL - 1);
    dnc(l + totL, r);
}

void dfs(int u)
{
    for (int i = 0; i < SZ(G[u]); ++i) {
        int v = G[u][i].x, w = G[u][i].y;
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1;
        fa[v] = u; fw[v] = w;
        dfs(v);
    }
}

void solve()
{
    for (int i = 1; i <= N; ++i) {
        id[i] = i;
        G[i].clear();
    }
    dnc(1, N);

    static int mincut[MAXN][MAXN];

    fa[1] = 0; dep[1] = 1;
    dfs(1);
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            int u = i, v = j;
            if (dep[u] < dep[v]) std::swap(u, v);
            mincut[i][j] = +oo;
            for (; dep[u] > dep[v]; u = fa[u]) chkmin(mincut[i][j], fw[u]);
            for (; u != v; u = fa[u], v = fa[v]) chkmin(mincut[i][j], std::min(fw[u], fw[v]));
        }
    }

    LL ans = 0;

    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            ans += std::min(mincut[i][j], 3);
        }
    }
    printf("%lld\n", ans);
}

int main()
{
    freopen("std.in", "r", stdin);
    freopen("bf.out", "w", stdout);

    int tt;
    read(tt);
    while (tt--) {
        input();
        solve();
    }

    return 0;
}

// 花似伊。柳似伊。花柳青春人别离。
//     -- 欧阳修《长相思·花似伊》

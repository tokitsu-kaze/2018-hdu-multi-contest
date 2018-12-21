#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
  
#define lowbit(x) ((x) & (-x))
  
LL pow_mod(LL b, LL p, LL k) {
    LL ret = 1;
    for (; p; p >>= 1) {
        if (p & 1) ret = ret * b % k;
        b = b * b % k;
    } return ret;
}
  
const int maxn = (int)(2e6) + 5;
const int mo = (int)(1e9) + 7;
  
int b[maxn], son[maxn];
vector<int> nxt[maxn], C[maxn];
LL f[maxn], g[maxn], fac[maxn], ret;
  
void dfs(int x, int fa) {
    f[x] = 1;
    if (fa) nxt[x].erase(find(nxt[x].begin(), nxt[x].end(), fa));
    son[x] = nxt[x].size(); nxt[x].insert(nxt[x].begin(), 0); C[x].push_back(0);
    for (int i = 1; i <= son[x]; ++i) {
        dfs(nxt[x][i], x); f[x] = f[x] * f[nxt[x][i]] % mo; C[x].push_back(0);
    } LL w;
    w = 1; for (int i = 1; i <= son[x]; ++i) g[nxt[x][i]] = w, w = w * f[nxt[x][i]] % mo;
    w = 1; for (int i = son[x]; i >= 1; --i) (g[nxt[x][i]] *= w) %= mo, w = w * f[nxt[x][i]] % mo;
    f[x] = f[x] * fac[son[x]] % mo;
}
  
void calcPre(int x, LL v) {
    int cnt = son[x];
    if (x == b[1]) --cnt;
    else if (x < b[1]) (ret += (f[x] * v % mo) * (cnt + 1) % mo) %= mo;
    for (int i = 1; i <= son[x]; ++i) calcPre(nxt[x][i], (v * g[nxt[x][i]] % mo) * fac[cnt] % mo);
}
  
inline void add(int p, int x, int v) {
    for (; x <= son[p]; x += lowbit(x)) C[p][x] += v;
}
  
inline int sum(int p, int x) {
    int ret = 0; for (; x; x -= lowbit(x)) ret += C[p][x]; return ret;
}
  
inline int findNxt(int p, int x) {
    int ps = 0;
    for (int i = 20; i >= 0; --i) if (ps + (1 << i) <= son[p] && nxt[p][ps + (1 << i)] < x) ps += (1 << i);
    return ps;
}
  
int idx;
bool calcNow(int x, LL v) {
    LL now = 1; ++idx;
    for (int i = 1; i <= son[x]; ++i) now = now * f[nxt[x][i]] % mo, add(x, i, 1);
    for (int i = son[x] - 1; i >= 0; --i) {
        int s = findNxt(x, b[idx + 1]);
        (ret += ((fac[i] * now % mo) * sum(x, s) % mo) * v % mo) %= mo; ++s;
        if (s > son[x] || nxt[x][s] != b[idx + 1]) return 1;
        add(x, s, -1); now = now * pow_mod(f[nxt[x][s]], mo - 2, mo) % mo;
        if (calcNow(nxt[x][s], (v * fac[i] % mo) * now % mo)) return 1;
    } return 0;
}

void solve () {
    int n; idx = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> b[i], nxt[i].clear(), C[i].clear();
    for (int i = 2; i <= n; ++i) {
        int u, v; cin >> u >> v;
        nxt[u].push_back(v); nxt[v].push_back(u);
    }
    b[n + 1] = 0; g[0] = 1; ret = 0;
    for (int i = 1; i <= n; ++i) sort(nxt[i].begin(), nxt[i].end());
    dfs(b[1], 0); calcPre(b[1], 1); calcNow(b[1], 1);
    cout << ret << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int MAX = (int)(1e6);
    fac[0] = 1;
    for (int i = 1; i <= MAX; ++i) fac[i] = fac[i - 1] * i % mo;
    int T; cin >> T;
    while (T--) solve();
    return 0;
}

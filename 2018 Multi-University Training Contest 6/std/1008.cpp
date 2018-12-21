#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define de(x) cout << #x << "=" << x << endl
#define rep(i,a,b) for(int i=a;i<b;++i)
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define fi first
#define se second

struct FastIO {
    static const int S = 1310720;
    int wpos;
    char wbuf[S];
    FastIO() :wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len)
            return -1;
        return buf[pos++];
    }
    inline int xuint() {
        int c = xchar(), x = 0;
        if (c == -1) return -1;
        while (c <= 32) {
            c = xchar();
            if (c == -1) return -1;
        }
        for (; '0' <= c && c <= '9'; c = xchar())
            x = x * 10 + c - '0';
        return x;
    }
} io;

const int N = 200005;
int n, TOT, an, idx, CNT;
bool vis[N * 8];
pii id[N * 8];
vector<pair<pii, pii> > E;
vi g[N * 8];
vector<pii> out;

struct Seg {
    int h, l, r, f;
    Seg() {}
    Seg(int h, int l, int r, int f = 1) : h(h), l(l), r(r), f(f) {}
    bool operator < (const Seg& c) const {
        if (h != c.h) return h < c.h;
        if (f != c.f) return f > c.f;
        return l < c.l;
    }
} s[2][N];

#define lson(x) (x<<1)
#define rson(x) ((x<<1)|1)

struct ND {
    int l, r, f, mi[2];
    void gao(int ff) {
        f += ff; mi[0] += ff; mi[1] += ff;
    }
} nd[N<<2];

void pd(int x) {
    if (nd[x].f){
        nd[lson(x)].gao(nd[x].f);
        nd[rson(x)].gao(nd[x].f);
        nd[x].f = 0;
    }
}

void pu(int x) {
    nd[x].mi[0] = min(nd[lson(x)].mi[0], nd[rson(x)].mi[0]);
    nd[x].mi[1] = max(nd[lson(x)].mi[1], nd[rson(x)].mi[1]);
}

void build(int l, int r, int x = 1) {
    nd[x].l = l; nd[x].r = r;
    nd[x].f = nd[x].mi[0] = nd[x].mi[1] = 0;
    if (l == r) return;
    int mid = (l + r)>>1;
    build(l, mid, lson(x));
    build(mid + 1, r, rson(x));
}

void add(int l, int r, int w, int x = 1) {
    if (nd[x].l >= l && nd[x].r <= r) {
        nd[x].gao(w);
        return;
    }
    pd(x);
    int mid = (nd[x].l + nd[x].r)>>1;
    if (l <= mid) add(l, r, w, lson(x));
    if (r > mid) add(l, r, w, rson(x));
    pu(x);
}

int ANS, TMP;
int h[N*2], hn;

bool get(int v, int x = 1) {
    if (nd[x].l >= v) {
        if ((nd[x].mi[!TMP] ? 1 : 0) == TMP) {
            ANS = nd[x].r;
            return true;
        }
    }
    if (nd[x].l == nd[x].r) {
        if (TMP == -1) {
            TMP = nd[x].mi[0] ? 1 : 0;
            ANS = nd[x].r;
            return true;
        }
        return false;
    }
    pd(x);
    int mid = (nd[x].l + nd[x].r)>>1, f;
    if (v <= mid) {
        if (get(v, lson(x))) f = get(v, rson(x));
        else f = 0;
    } else f = get(v, rson(x));
    pu(x);
    return f;
}

int find(int x) {return lower_bound(h + 1, h + 1 + hn, x) - h;}
int H(pii x) {return lower_bound(id + 1, id + 1 + idx, x) - id;}

void solve(Seg *s, int f) {
    sort(s + 1, s + n + 1);
    hn = 0; for (int i = 1; i <= n; i++) h[++hn] = s[i].l, h[++hn] = s[i].r;
    sort(h + 1, h + 1 + hn); hn = unique(h + 1, h + 1 + hn) - h - 1;
    build(1, hn - 1);
    for (int i = 1; i <= n; i++) {
        int j = i, rr = s[i].r;
        for (; j <= n; j++) {
            if (s[j].f == s[i].f && s[j].h == s[i].h && rr >= s[j].l) rr = max(rr, s[j].r);
            else break;
        }
        int l = find(s[i].l), r = find(rr) - 1;
        if (s[i].f == 1) {
            int u = l;
            while (u <= r) {
                TMP = -1; get(u);
                if (TMP == 0) {
                    int H = abs(s[i].h), L = h[u], R = h[min(r, ANS) + 1]; pii A, B;
                    if (!f) A = mp(H, L), B = mp(H, R); else A = mp(L, H), B = mp(R, H);
                    id[++idx] = A; id[++idx] = B;
                    if (sz(E) > 4 * n) return;
                    E.pb(mp(A, B));
                }
                u = ANS + 1;
            }
        }
        add(l, r, s[i].f);
        i = j - 1;
    }
}

void add_e(pii a, pii b) {
    int u = H(a), v = H(b);
    g[u].pb(v); g[v].pb(u);
}

bool dfs(int u) {
    CNT++; vis[u] = 1; out.pb(id[u]);
    if (sz(g[u]) != 2) return false;
    for (int i = 0; i < sz(g[u]); i++) {
        int v = g[u][i];
        if (!vis[v] && !dfs(v)) return false;
    }
    return true;
}

bool gao() {
    sort(id + 1, id + 1 + idx);
    idx = unique(id + 1, id + 1 + idx) - id - 1;
    for (int i = 1; i <= idx; i++) g[i].clear(), vis[i] = 0;
    for (int i = 0; i < sz(E); i++) add_e(E[i].fi, E[i].se);
    CNT = 0; out.clear();
    return dfs(1) && CNT == idx;
}

int main(){
    int T = io.xuint();
    while(T--) {
        n = io.xuint();
        for (int i = 1; i <= n; i++) {
            int xa = io.xuint(), ya = io.xuint(), xb = io.xuint(), yb = io.xuint();
            s[0][i*2-1] = Seg(xa, ya, yb, 1); s[0][i*2] = Seg(xb, ya, yb, -1);
            s[1][i*2-1] = Seg(ya, xa, xb, 1); s[1][i*2] = Seg(yb, xa, xb, -1);
        }
        n *= 2; idx = 0; E.clear();
        for (int i = 0; i < 2; i++) {
            solve(s[i], i);
            for (int j = 1; j <= n; j++) s[i][j].f *= -1, s[i][j].h *= -1;
            solve(s[i], i);
        }
        if (sz(E) <= 4 * n && gao()) {
            int v0 = 0;
            for (int i = 0; i < sz(out); i++) if(out[i] < out[v0]) v0 = i;
            int v1 = (v0 + 1) % sz(out), ad = (out[v0].fi != out[v1].fi ? -1 : 1);
            printf("%d\n", sz(out));
            for (int i = 0; i < sz(out); i++) {
                printf("%d %d\n", out[v0].fi, out[v0].se);
                v0 = (v0 + ad + sz(out)) % sz(out);
            }
        } else printf("Oops!\n");
    }
    return 0;
}
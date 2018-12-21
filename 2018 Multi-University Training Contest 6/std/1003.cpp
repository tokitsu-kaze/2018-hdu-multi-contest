#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
#define pb push_back
#define rep(i,l,r) for(int i=(l);i<(r);++i)
//-----
const int N = 5e5 + 7;
struct FastIO {
    static const int S = 1310720;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) { }
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len) pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) return -1;
        return buf[pos++];
    }
    inline int xint() {
        int c = xchar(), x = 0, s = 1;
        while (c <= 32) c = xchar();
        if (c == '-') s = -1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x * s;
    }
    ~FastIO() {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;
int n, L;
ll a[N], b[3 * N];
int go(int i, int lo) { while (b[i] < lo) i++; return i; }

int l[N], r[N * 3];
vector<ll> g[N];
void solve() {
	rep(i, 0, n) a[i] = io.xint(), a[i] += L;
	rep(i, 0, n) b[i] = io.xint();
	rep(i, 0, n * 2) b[i + n] = b[i] + L;
	rep(i, 0, n) {
		l[i] = go(!i ? 0 : l[i - 1], a[i] - L / 2);
		r[i] = go(!i ? 0 : r[i - 1], a[i] + 1);
	}
	rep(i, 0, n) l[i] -= i, r[i] -= i;
	int bg = -INT_MAX; rep(i, 0, n) bg = max(bg, l[i]);
	int ed =  INT_MAX; rep(i, 0, n) ed = min(ed, l[i] + n);

	rep(i, 0, ed - bg) g[i].clear();
	rep(i, 0, n) g[0].pb(a[i]);
	rep(i, 0, n) if (r[i] < ed) g[max(0, r[i] - bg)].pb(-2 * a[i]);

	r[bg] = a[0] < b[bg] ? 0 : -1;
	rep(i, bg + 1, 3 * n) {
		r[i] = r[i - 1];
		while (r[i] < min(i - bg, n - 1) && a[r[i] + 1] < b[i]) r[i]++;
	}
	rep(i, bg, 3 * n) {
		if (i - n + 1 < ed) g[max(i - n + 1 - bg , 0)].pb(-b[i]);
		if (~r[i] && i - r[i] < ed) {
			g[i - r[i] - bg].pb(2 * b[i]);
			if (i + 1 < ed) g[i + 1 - bg].pb(-b[i]);
		}
		else if (i + 1 < ed) g[i + 1 - bg].pb(b[i]);
	}

	ll tmp = 0, ans = LLONG_MAX;
	rep(i, 0, ed - bg) {
		for (auto e : g[i]) tmp += e;
		ans = min(ans, tmp);
	}
	cout << ans <<  endl;
}
int main() {
    //freopen("xx.in", "r", stdin);
    int tcas = io.xint();
    rep(cas, 0, tcas) {
        n = io.xint();
        L = io.xint();
        solve();
    }
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pw(x) (1 << (x))
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl

//-----
const int N = 22, M = 2e2 + 7;

int ans[M];
struct List {
	static const int N = 1e2 + 7;
	int m, sz, l[N], r[N];
	void ini(int n) {
		sz = n;
		rep(i, 0, n + 1) r[i] = i + 1;
		rep(i, 1, n + 2) l[i] = i - 1;
		m = n + 1 >> 1;
	}
	pii st[1000000]; int tp;
	void del(int p) {
		st[++tp].se = m;
		if (sz & 1) { if (p >= m) m = l[m]; }
		else { if (p <= m) m = r[m]; }
		st[tp].fi = p;
		r[l[p]] = r[p];
		l[r[p]] = l[p];
		sz--;
	}
	void pop() { r[l[st[tp].fi]] = l[r[st[tp].fi]] = st[tp].fi; m = st[tp--].se; sz++; }
	int mid() { return (sz & 1) ? (ans[m] << 1) : (ans[m] + ans[r[m]]); }
}	L;

int n, m, val[M][M], pos[M][M];
pair<int, vi> c[N];
int res, cur[M];
int cnt = 0;
void dfs(int u, int s) {
	res = max(res, L.mid() - s);
	per(i, 0, __builtin_ctz(u)) {
		for (auto e : c[i].se) L.del(pos[e][cur[e]--]);
		dfs(u | pw(i), s - c[i].fi);
		for (auto e : c[i].se) cur[e]++, L.pop();
	}
}
void solve() {
    cin >> n >> m;
	rep(i, 0, n) cin >> c[i].fi;
	rep(i, 0, n) {
		int sz; cin >> sz;
		c[i].se.resize(sz);
		rep(j, 0, sz) cin >> c[i].se[j];
	}
	sort(c, c + n, [](const pair<int, vi> &a, const pair<int, vi> &b){ return sz(a.se) < sz(b.se); });
	vector<pair<int, pii> > v;
	v.clear();
	rep(i, 1, m + 1) {
		cin >> cur[i];
		rep(j, 1, cur[i] + 1) {
			cin >> val[i][j];
			v.pb({val[i][j], {i, j}});
		}
	}
	sort(all(v));
	rep(i, 0, sz(v)) pos[v[i].se.fi][v[i].se.se] = i + 1;
	L.ini(sz(v));
	ans[0] = ans[sz(v) + 1] = -1000000000;
	rep(i, 0, sz(v)) ans[i + 1] = v[i].fi;
	int tmp = 0;
	rep(i, 0, n) tmp += c[i].fi;
	res = -INT_MAX;
	dfs(pw(n), tmp);
	cout << res << endl;
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int tcas; cin >> tcas;
    rep(cas, 0, tcas) solve();

	return 0;
}

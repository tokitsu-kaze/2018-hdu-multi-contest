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
#define pw(x) (1ll << (x))
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
#define inv(d) qpow(d, MOD - 2)
//-----
const int N = 13e5 + 7, MOD = 1e9 + 7;
int add(int a, int b) { if ((a += b) >= MOD) a -= MOD; return a; }
int mul(int a, int b) { return ll(a) * b % MOD; }
int qpow(int a, int b) { int r = 1; for (; b; b >>= 1) { if (b & 1) r = mul(r, a); a = mul(a, a); } return r; }
int f(int q, int n) { return q == 1 ? n : mul(add(qpow(q, n + 1), MOD - q), inv(q - 1)); }

int isp[N], p[N], pn;
void ini() {
	fill_n(isp + 2, N - 2, 1);
	rep(i, 2, N) {
		if (isp[i]) p[pn++] = i;
		for (int j = 0; j < pn && i * p[j] < N; j++) {
			isp[i * p[j]] = 0;
			if (i % p[j] == 0) break;
		}
	}
	assert(pn >= 100000);
}

int c, n, k, inv[N];
void solve() {
	int p = ::p[c - 1], tmp = p, ans = 0;
	rep(j, 1, k + 1) {
		tmp = mul(tmp, mul(j + p, inv[j + 1]));
        assert(tmp >= 1);
		ans = add(ans, f(tmp, n));
	}
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	rep(i, 1, 100007) inv[i] = inv(i);
	ini();
	int tcas; cin >> tcas;
	rep(cas, 0, tcas) {
        cin >> c >> n >> k;
        solve();
	}
	return 0;
}

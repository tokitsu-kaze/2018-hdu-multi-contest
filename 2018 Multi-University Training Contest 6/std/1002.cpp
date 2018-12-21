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
#define inv(x) qpow(x, MOD - 2)
//-----
const int N = 2e6 + 7, MOD = 1e9 + 7;
int add(int a, int b) { if ((a += b) >= MOD) a -= MOD; return a; }
int mul(int a, int b) { return ll(a) * b % MOD; }
int qpow(int a, int b) { int r = 1; for (; b; b >>= 1) { if (b & 1) r = mul(r, a); a = mul(a, a); } return r; }
int n, k;

int f[N], jc[N], ijc[N];
int gao(int d) { return add(qpow(2, f[d] + (d <= 47 ? 0 : MOD - 1)), MOD - 1); }
int C(int a, int b) { return mul(jc[a], mul(ijc[a - b], ijc[b])); }
void ini() {
	f[1] = 1; f[2] = 1;
	rep(i, 3, N) if ((f[i] = f[i - 2] + f[i - 1]) >= MOD - 1) f[i] -= MOD - 1;
	jc[0] = 1; rep(i, 1, N) jc[i] = mul(jc[i - 1], i);
	ijc[N - 1] = inv(jc[N - 1]); per(i, 0, N - 1) ijc[i] = mul(ijc[i + 1], i + 1);
	//rep(i, 0, 10) rep(j, 0, i + 1) cout << C(i, j) << " \n"[j == i];
}
int dp[N];
void solve() {
	cin >> n >> k;
	vi v;
	for (int i = 1; i * i <= n; i++) if (n % i == 0) {
		v.pb(i);
		if (i * i < n) v.pb(n / i);
	}
	sort(all(v));
	int ans = 0;
	per(i, 0, sz(v)) {
		int t = v[i];
		dp[i] = C(n / v[i] + k - 1, k - 1);
		per(j, i + 1, sz(v)) if (v[j] % v[i] == 0) dp[i] = add(dp[i], MOD - dp[j]);
		ans = add(ans, mul(gao(v[i]), dp[i]));
	}
	cout << mul(ans, inv(C(n + k - 1, k - 1))) << endl;
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	ini();
	int tcas; cin >> tcas;
	rep(cas, 0, tcas) solve();
	return 0;
}

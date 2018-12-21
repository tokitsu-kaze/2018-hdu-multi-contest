#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, int> pii;

int pr[305], chk[305], cnt;

const int maxM = (int)(1e6);
const int maxK = 240;
const LL MAX = (LL)(1e18) + maxM;
const LL K = 233;

pii b[maxM], c[maxM];
int mx[maxK], ps[maxK];
LL va[maxM * 10];
int tot;

void upd(int x) {
	int p = K; while(p && mx[p - 1] < x) --p;
	for (int i = K; i > p; --i) mx[i] = mx[i - 1]; 
	mx[p] = x;
 }

bool valid(LL a, LL b) {
	LL ret = 0;
	for (; b; b >>= 1) {
		if (b & 1) {
			ret += a;
			if (a < 0 || ret >= MAX) return 0;
		}
		a += a; if (a >= MAX) a = -1;
	} return 1;
}

void gen() {
	int M = 293;
	for (int i = 2; i <= M; ++i) if (!chk[i]) {
		pr[++cnt] = i;
		for (int j = i + i; j <= M; j += i) chk[j] = 1;
	}
	tot = 0; b[++tot] = make_pair(1, 1);
	for (int i = 1; i <= cnt; ++i) {
		LL now = pr[i]; int idx = 0;
		for (int j = 1; j <= tot; ++j) {
			c[++idx] = b[j]; int w = 0;
			LL va = b[j].first; int di = b[j].second;
			while (valid(va, now)) {
				va *= now; ++w;
				c[++idx] = make_pair(va, di * (w + 1));
			}
		}
		sort(c + 1, c + idx + 1); tot = 0; 
		memset(mx, 0, sizeof(mx));
		for (int j = 1; j <= idx; ++j) {
			if (c[j].second >= mx[K]) {
				upd(c[j].second); b[++tot] = c[j];
			}
		}
	}
	int cur = 0;
	for (int i = 0; i <= K; ++i) {
		int cnt = 0;
		ps[i] = cur + 1;
		memset(mx, 0, sizeof(mx));
		for (int j = 1; j <= tot; ++j) {
			if (b[j].second >= mx[i]) {
				upd(b[j].second); va[++cur] = b[j].first - (cnt++);
			}
		}
	}
	ps[K + 1] = cur + 1;
}

void solve () {
	LL n; int m;
	cin >> n >> m;
	int p = upper_bound(va + ps[m], va + ps[m + 1], n) - va - ps[m];
	cout << n + p << endl;
}

int main () {
	ios::sync_with_stdio(false);
	int T;
	cin >> T; gen();
	while (T--) solve();
	return 0;
}
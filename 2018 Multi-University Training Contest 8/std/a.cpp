#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;

const LL mod = 998244353;
LL fact[200005], ifact[200005], inv[200005];

void init() {
    fact[0] = 1;
    Rep (i, 200000) fact[i] = fact[i-1] * i % mod;
    inv[1] = 1;
    for (int i = 2; i <= 200000; i++)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    ifact[0] = 1;
    Rep (i, 200000) ifact[i] = ifact[i-1] * inv[i] % mod;
}

LL binom(LL m, LL n) {
    return fact[m] * ifact[n] % mod * ifact[m-n] % mod;
}

LL subsolve(LL n, LL m) {
    if (m < 0) return 0;
    return binom(m+n-1, n-1);
}

LL tmp[100005];

int main() {
    init();
    int T; cin >> T;
    while (T--) {
        LL n, m, k; cin >> n >> m >> k;
        for (int i = 0; i <= m; i++)
            tmp[i] = binom(m, i) * subsolve(m, k-i*n) % mod;
        for (int i = m-1; i>=0; i--) tmp[i] = (tmp[i] + mod - tmp[i+1]) % mod;
        cout << tmp[0] << endl;
    }
    return 0;
}

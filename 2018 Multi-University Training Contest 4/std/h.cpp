#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL pow_mod(LL b, LL p, LL k) {
    LL ret = 1;
    for (; p; p >>= 1) {
        if (p & 1) ret = ret * b % k;
        b = b * b % k;
    }
    return ret;
}

const int maxn = 305;
const int mo = (int)(1e9) + 7;
const LL mo2 = 1LL * mo * mo;
int a[maxn], b[maxn];
LL fac[maxn], ivf[maxn], h[maxn];
LL C[maxn][maxn];
LL g1[maxn][maxn];
LL g2[maxn][maxn];
LL l0[maxn][maxn];
LL l1[maxn][maxn];
LL r0[maxn][maxn];
LL r1[maxn][maxn];
LL pw[maxn];

LL P;

void add(LL& x, LL v) {
    x += v; if (x >= mo2) x -= mo2;
}

void gen () {
    int M = 300;
    fac[0] = ivf[0] = 1;
    for (int i = 1; i <= M; ++i) fac[i] = fac[i - 1] * i % mo;
    ivf[M] = pow_mod(fac[M], mo - 2, mo);
    for (int i = M - 1; i >= 1; --i) ivf[i] = ivf[i + 1] * (i + 1) % mo;
    for (int i = 0; i <= M; ++i) C[i][0] = 1;
    for (int i = 1; i <= M; ++i) for (int j = 1; j <= i; ++j) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mo;

    for (int i = 0; i <= M; ++i) h[i] = ((i & 1) ? mo - 1 : 1) * ivf[i] % mo;
}

void solve () {
    int n, _p, _q;
    cin >> n;
    cin >> _p >> _q;
    P = (1 + (mo -_p) * pow_mod(_q, mo - 2, mo)) % mo;
    pw[0] = 1;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; b[i] = 0; pw[i] = pw[i - 1] * P % mo;
        for (int j = 1; j < i; ++j) if (a[j] < a[i]) ++b[i];
    }
    
    memset(g2, 0, sizeof(g2));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n - i; ++j) {
        g1[i][j] = pow_mod(P, n - 1 - i, mo) * ivf[i] % mo * ivf[j] % mo * pow_mod((1 + mo - pow_mod(P, n - i - j, mo)), mo - 2, mo) % mo;
        for (int k = 0; k < n - i - j; ++k) add(g2[i + k][j], g1[i][j] * h[k]);
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < n - i; ++j) g2[i][j] %= mo;
    memset(g1, 0, sizeof(g1));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n - i; ++j) {
        for (int k = 0; k < n - i - j; ++k) add(g1[i][j + k], g2[i][j] * h[k]);
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < n - i; ++j) g1[i][j] = g1[i][j] % mo * fac[i] % mo * fac[j] % mo;

    for (int i = 1; i <= n; ++i) for (int j = 0; j < n; ++j) {
        l0[i][j] = l1[i][j] = r0[i][j] = r1[i][j] = 0;
        for (int k = 0; k <= j; ++k) {
            LL v = C[b[i]][k] * C[i - b[i] - 1][j - k] % mo;
            add(l0[i][j], v); add(l1[i][j], v * k);
            v = C[a[i] - b[i] - 1][k] * C[n - i - a[i] + b[i] + 1][j - k] % mo;
            add(r0[i][j], v); add(r1[i][j], v * k);
        }
        l0[i][j] %= mo; l1[i][j] %= mo; r0[i][j] %= mo; r1[i][j] %= mo;
    }
    
    LL ret = 0;
    for (int i = 1; i <= n; ++i) for (int j = 0; j < i; ++j) for (int k = 0; k <= n - i; ++k) {
        LL w = (l0[i][j] * r0[i][k] % mo * (a[i] - 1) + (mo - l1[i][j]) * r0[i][k] + (mo - l0[i][j]) * r1[i][k]) % mo;
        add(ret, fac[n - j - k - 1] * g1[j][k] % mo * pw[i] % mo * w);
    }

    ret = ret % mo * pow_mod(pow_mod(P, n, mo), mo - 2, mo) % mo * (1 + mo - P) % mo;
    cout << (ret + 1) % mo << endl;
}

int main () {
    gen();
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}

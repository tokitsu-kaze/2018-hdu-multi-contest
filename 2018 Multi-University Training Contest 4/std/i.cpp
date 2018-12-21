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

const int maxn = (int)(3e5) + 5;
const int mo = 998244353;
const int rt = 3;
LL fac[maxn], ivf[maxn], B[maxn];
LL T[2][maxn], P[maxn], Q[maxn];
int K;

inline LL C(int n, int m) {
    return fac[n] * ivf[m] % mo * ivf[n - m] % mo;
}

void ntt(LL a[], int n, int d = 1) {
	for (int i = (n >> 1), j = 1; j < n; ++j) {
		if (i < j) swap(a[i], a[j]);
		int k; for (k = (n >> 1); i & k; i ^= k, k >>= 1); i ^= k;
	}
	for (int m = 2; m <= n; m <<= 1) {
		LL w = pow_mod(rt, 1LL * (mo - 1) / m * (mo - 1 + d), mo);
		for (int i = 0; i < n; i += m) {
			LL s = 1;
			for (int j = i; j < i + (m >> 1); ++j) {
				LL u = a[j], v = a[j + (m >> 1)] * s % mo;
				a[j] = u + v; a[j + (m >> 1)] = u - v; s = s * w % mo;
				if (a[j] >= mo) a[j] -= mo; 
				if (a[j + (m >> 1)] < 0) a[j + (m >> 1)] += mo;

			}
		}
	}
	if (d == -1) {
		LL xinv = pow_mod(n, mo - 2, mo);
		for (int i = 0; i < n; ++i) a[i] = a[i] * xinv % mo;
	}
}

void inverse(LL a[], LL b[], LL c[], int n) {
    int stk[22];
    for (stk[0] = 0; n > 1; stk[++stk[0]] = n, n = (n + 1) >> 1);
    b[0] = pow_mod(a[0], mo - 2, mo);
    for (int i = stk[0]; i >= 1; --i) {
        int m = stk[i], len = 0;
        while ((1 << len) < (m << 1)) ++len;
        for (int i = 0; i < m; ++i) c[i] = a[i];
        for (int i = m; i < (1 << len); ++i) c[i] = 0;
        ntt(b, 1 << len); ntt(c, 1 << len);
        for (int i = 0; i < (1 << len); ++i) b[i] = ((mo - c[i]) * b[i] + 2) % mo * b[i] % mo;
        ntt(b, 1 << len, -1);
        for (int i = m; i < (1 << len); ++i) b[i] = 0;
    }
}

void gen() {
    fac[0] = ivf[0] = 1;
    int M = (int)(1e5) + 1;
    for (int i = 1; i <= M; ++i) fac[i] = fac[i - 1] * i % mo;
    ivf[M] = pow_mod(fac[M], mo - 2, mo);
    for (int i = M - 1; i >= 1; --i) ivf[i] = ivf[i + 1] * (i + 1) % mo;
    for (int i = 0; i < M; ++i) T[0][i] = ivf[i + 1];
    inverse(T[0], B, T[1], M);
    for (int i = 0; i < M; ++i) B[i] = B[i] * fac[i] % mo;
    ++B[1];
}

int ai[25], bi[25];

void solve() {
    LL N = 1; int M;
    scanf("%d%d", &K, &M);
    for (int i = 1; i <= M; ++i) {
        scanf("%d%d", &ai[i], &bi[i]); N = N * pow_mod(ai[i], bi[i], mo) % mo;
    }
    memset(T, 0, sizeof(T));
    for (int i = 0; i <= K; ++i) T[0][i] = ivf[K - i] * B[K - i] % mo;
    for (int i = 0; i <= K + 1; ++i) T[1][i] = ivf[i + 1] * pow_mod(N, i + 1, mo) % mo;
    reverse(T[1], T[1] + K + 2);
    int len = 0;
    while ((1 << len) < ((K + 1) << 1)) ++len;
    ntt(T[0], 1 << len); ntt(T[1], 1 << len);
    for (int i = 0; i < (1 << len); ++i) T[0][i] = T[0][i] * T[1][i] % mo;
    ntt(T[0], 1 << len, -1);
    for (int i = K; i <= 2 * K + 1; ++i) {
        int dt = i - K; P[dt] = T[0][i] * fac[K] % mo * B[dt] % mo * ivf[dt] % mo;
    }
    for (int i = 0; i <= K + 1; ++i) Q[i] = 1;
    for (int i = 1; i <= M; ++i) {
        LL p = ai[i] % mo; LL now = pow_mod(p, mo - 2, mo);
        for (int j = 0; j <= K + 1; ++j) Q[j] = Q[j] * (1 + mo - now) % mo, now = now * p % mo;
    }
    LL ret = 0;
    for (int i = 0; i <= K + 1; ++i) (ret += P[i] * Q[i]) %= mo;
    printf("%lld\n", ret);
}

int main () {
    gen();
    int T;
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}
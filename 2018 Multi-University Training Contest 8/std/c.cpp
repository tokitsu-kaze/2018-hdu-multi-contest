#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
    __func__, ##__VA_ARGS__)
#else 
# define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;

const int MAXN = 32;
const LL mod = 998244353;

struct matrix {
  LL m[MAXN][MAXN];

  void operator *=(matrix& a) {
    static LL t[MAXN][MAXN];
    rep (i, MAXN) {
      rep (j, MAXN) {
        t[i][j] = 0;
        rep (k, MAXN) {
          t[i][j] += (m[i][k] * a.m[k][j]) % mod;
          if (t[i][j] >= mod) t[i][j] -= mod;
        }
      }
    }
    memcpy(m, t, sizeof t);
  }
};

matrix r;
void m_powmod(matrix& b, LL e) {
  memset(r.m, 0, sizeof(r.m));
  rep (i, MAXN) r.m[i][i] = 1;
  while (e) {
    if (e&1) r*=b;
    b*=b;
    e>>=1;
  }
}

#define div arngsgrto
int n, k;
LL T;
pair<int, int> div[300005];
int d[300005];
LL e[32], N[32];
vector<LL> res;

void update_ans(int l, int r, LL inc) {
  res[r] += mod - inc; if (res[r] >= mod) res[r] -= mod;
  res[l] += inc; if (res[l] >= mod) res[l] -= mod;
}

int main() {
  int K; scanf("%d", &K);
  while (K--) {
    cin >> n >> k >> T;
    div[k].first = n;
    Rep (i, k) scanf("%d", &div[k-i].first);
    rep (i, n) scanf("%d", &d[i]);
    rep (i, k+1) scanf("%d", &div[k-i].second);
    k = unique(div, div + k + 1, [] (pair<int, int> x, pair<int, int> y) {
          return x.first == y.first;
        }) - div;
    rep (i, k) tie(N[i], e[i]) = div[i];

//    for (int i = k-1; i; i--) div[i].second -= div[i-1].second;
    rep (i, k) _debug("N[%d]=%lld, e[%d]=%lld", i, N[i], i, e[i]);
    matrix a;
    memset(&a, 0, sizeof a);
    LL acc = e[0];
    for (int i = 0; i < k; i++) {
      a.m[i][0] = e[i];
      for (int j = 1; j < k; j++) {
        if (i != j) {
          a.m[i][j] = e[max(i, j)] * (N[j] - N[j-1]) % mod;
        } else {
          a.m[i][j] = (acc + e[i] * (N[i] - N[i-1] - N[i-1])) % mod;
          acc = (acc + e[i] * (N[i] - N[i-1])) % mod; 
        }
      }
    }
//    rep (i, k) { rep (j, k) printf("%lld\t", a.m[i][j]); puts(""); }
    m_powmod(a, T);
    LL g[32]; rep (i, k) g[i] = r.m[i][0];
    rep (i, k) _debug("g[%d]=%lld", i, g[i]);
    for (int i = 1; i < k; i++) g[i-1] = (g[i-1] + mod - g[i]) % mod;
//    for (int i = k; i; i--) g[i] = (g[i] + mod - g[i-1]) % mod;
    res.assign(n+1, 0);
    rep (i, n) {
      rep (j, k) {
        int lbnd = i / N[j] * N[j], rbnd = lbnd + N[j];
        update_ans(lbnd, rbnd, 1ll * d[i] * g[j] % mod);
      }
    }
    partial_sum(res.begin(), res.begin() + n, res.begin(), [] (LL a, LL b) {
          LL c = a + b; if (c >= mod) c -= mod; return c;
        });
    rep (i, n) printf("%d%c", int(res[i]), i==n-1?'\n':' ');
  }
  return 0;
}


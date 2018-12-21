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

constexpr int MAXM = 12;
LL dp[32][1<<MAXM], fact[32];
LL ans[32];
unsigned a[32];
char g[32][32];
int rcnt[32];
int m, n, k;

void print64mul(LL x, LL y) {
#if __SIZEOF_INT128__ == 16
  __int128 res = __int128(x) * y;
  char ch[64];
  int ptr = 0;
  if (res == 0) {
    puts("0");
    return;
  }
  while (res) {
    ch[ptr] = (res % 10) + '0';
    ptr++;
    res /= 10;
  }
  while (ptr)
    putchar(ch[--ptr]);
  putchar('\n');
#else
  constexpr LL limit = 1000000000;
  LL dig[4] = {0};
  dig[0] = x % limit;
  dig[1] = x / limit;
  dig[0] *= y;
  dig[1] *= y;
  dig[1] += dig[0] / limit;
  dig[0] %= limit;
  dig[2] += dig[1] / limit;
  dig[1] %= limit;
  int pos = 2;
  while (pos > 0) {
    if (dig[pos]) break;
    pos--;
  }
  printf("%d", dig[pos]);
  while (pos > 0) {
    pos--;
    printf("%09d", dig[pos]);
  }
  puts("");
#endif
}

int main() {
  int T; scanf("%d", &T);
  fact[0] = 1;
  Rep (i, 20) fact[i] = fact[i-1] * i;
  while (T--) {
    scanf("%d%d%d", &m, &n, &k);
    rep (i, m) scanf("%s", g[i]);
    memset(a, 0, sizeof a);
    memset(rcnt, 0, sizeof rcnt);
    Rep (j, n) rep (i, m) {
      a[j] = a[j] << 1 | (g[i][j-1] == 'Q');
      if (g[i][j-1] == 'Q') {
        rcnt[i]++;
      }
    }
    memset(ans, 0, sizeof ans);
    for (unsigned fin = 1; fin < (1u << m); fin++) {
      dp[0][0] = 1;
      Rep (r, n) {
        bool flag = false;
        for (unsigned mask = fin; ; mask = (mask - 1) & fin) {
          if (dp[r - 1][mask]) {
            if ((a[r] & fin) == a[r]) {
              if (dp[r][mask] += dp[r-1][mask]) flag = true; 
            }
            for (unsigned dif = (fin ^ mask) & a[r]; dif; dif &= dif - 1) {
              unsigned bit = dif & -dif;
              dp[r][mask | bit] += dp[r-1][mask];
              flag = true;
            }
            dp[r-1][mask] = 0;
          }
          if (mask == 0) break;
        }
        if (flag == false) break;
      }
      ans[__builtin_popcount(fin)] += dp[n][fin];
      for (unsigned mask = fin; ; mask = (mask - 1) & fin) {
        dp[n][mask] = 0;
        if (mask == 0) break;
      }
    }
    Rep (i, k) print64mul(ans[i], fact[i]);
  }
  return 0;
}


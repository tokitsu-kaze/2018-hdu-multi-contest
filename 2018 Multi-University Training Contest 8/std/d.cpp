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

int m, n;
bool rev;
char g[256][256];

int main() {
  int T; cin >> T;
  while (T--) {
    cin >> m >> n;
    memset(g, 0, sizeof g);
    rev = false;
    if (m & 1) {
      rep (i, m) rep (j, n) g[i][j] = (j >= n/2 ? ')' : '(');
    } else if (n & 1) {
      rep (i, m) rep (j, n) g[i][j] = (i >= m/2 ? ')' : '(');
    } else {
      if (m > n) {
        swap(m, n);
        rev = true;
      }
      switch (m) {
        case 2:
          rep (i, n) {
            g[0][i] = '(';
            g[1][i] = ')';
          }
          break;
        case 4:
          rep (i, n) {
            g[0][i] = '(';
            g[1][i] = (i < n/2 ? ')' : '(');
            g[2][i] = (i < n/2 ? '(' : ')');
            g[3][i] = ')';
          }
          break;
        default:
          rep (i, m) rep (j, n) {
            if (i == 0 || j == 0) g[i][j] = '(';
            else if (i == m-1 || j == n-1) g[i][j] = ')';
            else if ((i^j)&1) g[i][j] = ')'; else g[i][j] = '(';
          }
      }
    }

    if (rev) {
      rep (j, n) {
        rep (i, m) putchar(g[i][j]);
        puts("");
      }
    } else {
      rep (i, m) {
        rep (j, n) putchar(g[i][j]);
        puts("");
      }
    }
  }
  return 0;
}


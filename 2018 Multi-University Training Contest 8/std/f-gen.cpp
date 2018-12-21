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

const LL mod = 998244353;
const int maxv = 13;

LL powmod(LL b, LL e) {
  LL r = 1;
  while (e) {
    if (e & 1) r = r * b % mod;
    b = b * b % mod;
    e >>= 1;
  }
  return r;
}

LL inv(LL x) { return powmod(x, mod - 2); }

LL fact[20], pow2[8192];
int lcm[32][32][32];

vector<pair<LL, vector<int>>> integer_partitions[20];

vector<int> current_partition;

void yield_partition() {
  map<int, int> cyc;
  int m = accumulate(range(current_partition), 0);
  LL cnt = fact[m];
  for (int x : current_partition) cyc[x]++;
  for (auto p : cyc) {
    cnt = cnt * inv(fact[p.second] * powmod(p.first, p.second) % mod) % mod;
  }
  integer_partitions[m].emplace_back(cnt, current_partition);
}

void enumerate_integer_partition(int l, int rem) {
  if (rem == 0) {
    yield_partition();
    return;
  }
  if (rem < l) {
    return;
  }
  for (int p = l; p <= rem; p++) {
    current_partition.push_back(p);
    enumerate_integer_partition(p, rem - p);
    current_partition.pop_back();
  }
}

const int MAXD = 64;
struct {
  ULL b[MAXD];
  int rank;

  void clear() {
    memset(b, 0, sizeof b);
    rank = 0;
  }

  bool insert(ULL v) {
    for (int j = MAXD - 1; j >= 0; j--) {
      if (!(v & (1ull << j))) continue;
      if (b[j]) v ^= b[j];
      else {
        for (int k = 0; k < j; k++)
          if (v & (1ull << k)) v ^= b[k];
        for (int k = j + 1; k < MAXD; k++)
          if (b[k] & (1ull << j)) b[k] ^= v;
        b[j] = v;
        rank++;
        return true;
      }
    }
    return false;
  }
} basis;

void init() {
  fact[0] = 1;
  Rep (i, 15) fact[i] = fact[i-1] * i % mod;
  Rep (i, maxv) { enumerate_integer_partition(1, i); }
  pow2[0] = 1;
  Rep (i, 8000) pow2[i] = pow2[i-1] * 2 % mod;
  Rep (u, 20) Rep (v, 20) Rep (w, 20)
    for (int i = max({u, v, w}); ;i++) {
      if (i % u || i % v || i % w) continue;
      lcm[u][v][w] = i;
      break;
    }
}

LL solve(int m, int n, int p) {
  LL tot = 0;
  for (auto& parx : integer_partitions[m]) {
    for (auto& pary : integer_partitions[n]) {
      for (auto& parz : integer_partitions[p]) {
        LL sz = parx.first * pary.first % mod * parz.first % mod;
        vector<int> px = parx.second, py = pary.second, pz = parz.second;
        int toti, totj, totk;

        basis.clear();
        toti = 0;
        for (int ci : px) {
          totj = 0;
          for (int dj : py) {
            totk = 0;
            for (int ek : pz) {
              int t = lcm[ci][dj][ek];
              sz = sz * pow2[ci * dj * ek / t] % mod;
              ULL bit1 = (t / ci) & 1,
                  bit2 = (t / dj) & 1,
                  bit3 = (t / ek) & 1;
              ULL v = 0;
              for (int i = toti; i < toti + ci; i++) v |= bit1 << (i + 32);
              for (int j = totj; j < totj + dj; j++) v |= bit2 << (j + 16);
              for (int k = totk; k < totk + ek; k++) v |= bit3 << k;
              basis.insert(v);
              totk += ek;
            }
            totj += dj;
          }
          toti += ci;
        }

        sz = sz * pow2[m * n * p - basis.rank] % mod;
        tot = (tot + sz) % mod;
      }
    }   
  }
  tot = tot * inv(powmod(2, m * n * p) * 
      fact[m] % mod * fact[n] % mod * fact[p] % mod) % mod;
  return tot;
}

int main() {
  init();
  puts("{");
  Rep (i, 13) {
    puts("  {");
    Rep (j, i) {
      printf("    {");
      Rep (k, j) {
        cerr << i << ' ' << j << ' ' << k << endl;
        printf("%d, ", (int)solve(i, j, k));
      }
      puts("},");
    }
    puts("  },");
  }
  puts("}");
  return 0;
}


#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
typedef long long LL;

struct stock {
  int tot = 0;
  int acc_cost = 0;
  map<int, int> s;

  /**
   * @brief Consume specified number of cheap objects.
   *
   * @param max_num the maximum number of objects to consume
   * @param fn callback function
   * @return the number of unsuccessfully consumed objects
   */
  template <typename T> 
  int consume(int max_num, T fn) {
    while (s.size() && max_num) {
      if (max_num >= s.begin()->second) {
        fn(s.begin()->second, s.begin()->first + acc_cost);
        max_num -= s.begin()->second;
        tot -= s.begin()->second;
        s.erase(s.begin());
      } else {
        fn(max_num, s.begin()->first + acc_cost);
        tot -= max_num;
        s.begin()->second -= max_num;
        max_num = 0;
      }
    }
    return max_num;
  }

  /**
   * @brief Discard expensive objects, leaving at most specified number objects.
   *
   * @param sz the maximum number of objects to retain
   */
  void discard_until(int sz) {
    while (tot > sz) {
      assert(s.size());
      int res = tot - s.rbegin()->second;
      if (res < sz) {
        s.rbegin()->second -= tot - sz;
        tot = sz;
      } else {
        tot = res;
        s.erase(prev(s.end()));
      }
    }
  }

  /**
   * @brief Add objects to stock.
   *
   * @param sz number of objects
   * @param cost unit cost
   */
  void push(int sz, int cost) {
    s[cost - acc_cost] += sz;
    tot += sz;
  }

  /**
   * @brief Increase the unit cost of the stock.
   *
   * @param delta the increment
   */
  void increase_cost(int delta) { acc_cost += delta; }
};

int k;
typedef int intarr[100005];
intarr c, d, m, p, e, R, E;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T; scanf("%d", &T);
  while (T--) {
    int min_raw_cost = INT_MAX;
    stock pro;
    LL tot_cost = 0;
    scanf("%d", &k);
    rep(i, k) scanf("%d%d%d%d", &c[i], &d[i], &m[i], &p[i]);
    rep(i, k - 1) scanf("%d%d%d", &e[i], &R[i], &E[i]);
    e[k - 1] = R[k - 1] = E[k - 1] = 0;
    rep(i, k) {
      min_raw_cost = min(min_raw_cost, c[i]);
      pro.push(p[i], min_raw_cost + m[i]);
      if (pro.consume(d[i], [&](int sz, int cost) {
            tot_cost += LL(cost) * sz;
          }) > 0) {
        tot_cost = -1;
        break;
      }
      pro.discard_until(e[i]);
      min_raw_cost += R[i];
      pro.increase_cost(E[i]);
    }
    cout << tot_cost << endl;
  }
  return 0;
}


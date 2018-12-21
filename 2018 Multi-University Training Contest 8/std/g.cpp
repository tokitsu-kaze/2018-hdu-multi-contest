#include <bits/stdc++.h>
using namespace std;

#define _debug(fmt, ...) fprintf(stderr, "> %s: " fmt "\n", \
    __func__, ##__VA_ARGS__)
#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

LL MOD = 998244353;

struct Solution {
  int n;
  vector<vector<pair<int, int>>> adj;
  vector<vector<int>> cc;
  vector<int> ufs;
  vector<int> flag, ring;
  vector<int> dcnt, revcnt;
  vector<pair<int, int>> ans;
  int vcnt = 0, ecnt = 0;

  int father(int x) {
    if (ufs[x] == x) return x;
    return ufs[x] = father(ufs[x]);
  }

  bool unite(int u, int v) {
    u = father(u);
    v = father(v);
    ufs[u] = v;
    return u != v;
  }

  void dfs(int u, int f) {
    if (flag[u] >= 0) return;
    flag[u] = f;
    cc.back().push_back(u);
    vcnt++;
    ecnt += adj[u].size();
    for (auto& p : adj[u]) dfs(p.first, f);
  }

  void find_ring(int u, int t, int eid, int pcnt, int ncnt) {
    // cerr << "find_ring " << u << ' ' << t << ' ' << pcnt << ' ' << ncnt << endl;
    if (ring[u]) return;
    ring[u] = true;
    if (u == t) throw make_pair(pcnt, ncnt);
    for (auto& e : adj[u]) {
      if (e.second == eid) continue;
      find_ring(e.first, t, -e.second, pcnt + (e.second > 0), ncnt + (e.second < 0));
    }
    ring[u] = false;
  }

  int tree_search(int u, int p) {
    // _debug("%d %d", u, p);
    int ans = 0;
    for (auto& e : adj[u]) {
      if (e.first == p) continue;
      ans += tree_search(e.first, u) + (e.second < 0);
    }
    return dcnt[u] = ans;
  }

  void rev_tree_search(int u, int p, int cnt) {
    revcnt[u] = cnt;
    for (auto& e : adj[u]) {
      if (e.first == p) continue;
      cnt += dcnt[e.first] + (e.second < 0);
    }
    for (auto& e : adj[u]) {
      if (e.first == p) continue;
      rev_tree_search(e.first, u, cnt - dcnt[e.first] + (e.second > 0) - (e.second < 0));
    }
  }

  void solve_t() {
    // _debug();
    int r = cc.back().front();
    tree_search(r, -1);
    rev_tree_search(r, -1, 0);
    int minn = INT_MAX, mincnt = 0;
    for (int v : cc.back()) {
      int val = dcnt[v] + revcnt[v];
      if (val == minn)
        mincnt++;
      else if (val < minn) {
        minn = val;
        mincnt = 1;
      }
    }
    ans.push_back({minn, mincnt});
  }

  void solve_pt() try {
    // _debug();
    for (int u : cc.back()) {
      for (auto& e : adj[u]) {
        if (e.second < 0) continue;
        if (unite(u, e.first) == false) {
          find_ring(u, e.first, e.second, 0, 1);
        }
      }
    }
  } catch (pair<int, int> e) {
    int num = min(e.first, e.second), ways = 1 + (e.first == e.second);
    /*
    for (int u : cc.back()) {
        if (ring[u]) cout << u << ' ';
    } cout << endl;
    */
    for (int u : cc.back()) {
      if (ring[u] == false) continue;
      for (auto& e : adj[u]) {
        if (ring[e.first]) continue;
        num += tree_search(e.first, u) + (e.second < 0);
      }

    }
    // cout << "PT: " << num <<  ' ' << ways << endl;;
    ans.push_back({num, ways});
  }

  Solution() {
    cin >> n;
    adj.resize(n + n);
    flag.resize(n + n, -1);  ring.resize(n + n);
    ufs.resize(n + n);       dcnt.resize(n + n);
    revcnt.resize(n + n);
    rep (i, n + n) ufs[i] = i;
    Rep (i, n) {
      int x, y;
      cin >> x >> y;
      x--; y--;
      adj[x].push_back({y, -i});
      adj[y].push_back({x, i});
    }
    rep (i, n + n) {
      if (flag[i] >= 0) continue;
      int lastv = vcnt, laste = ecnt;
      cc.push_back({});
      dfs(i, i);
      switch (2 * (vcnt - lastv) - (ecnt - laste)) {
        case 2:  //  tree
          solve_t();
          break;
        case 0:  //  pseudotree
          solve_pt();
          break;
        default:
          cout << "-1 -1" << endl;
          return;
      }
    }
    auto p = accumulate(
        range(ans), make_pair(0, 1),
        [](pair<int, int> l, pair<int, int> r) -> pair<int, int> {
          return {l.first + r.first, 1ll * l.second * r.second % MOD};
        });
    cout << p.first << ' ' << p.second << endl;
    return;
  }
};

int main() {
  // freopen("std.in", "r", stdin);
  int T;
  cin >> T;
  while (T--)
    Solution sol;
  return 0;
}


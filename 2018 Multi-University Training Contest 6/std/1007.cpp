// #include {{{
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
#include <bitset>
#include <vector>
#include <complex>
#include <algorithm>
#include <climits> // newly added header file
using namespace std;
// }}}
// #define {{{
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define de(x) cout << #x << "=" << x << endl
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define fi first
#define se second
// }}}

const int N = 1e5 + 10 , M = 2e5 + 10 , P = 998244353;
const ll inf = 1ll<<62;

struct LCT {
  static const int N = ::N + ::M;
  bool rt[N], rev[N];
  int n, fa[N], que[N], ch[N][2];
  // custom information
  int mn[N], val[N];
  void init(int _n) {
    n = _n;
    rep(i, 0, n) {
      rt[i] = true, rev[i] = false;
      fa[i] = ch[i][0] = ch[i][1] = 0;
    }
  }
  void reverse(int x) {
    rev[x] = !rev[x], swap(ch[x][0], ch[x][1]);
  }
  void up(int x) {
    mn[x] = val[x];
    rep(i, 0, 2) if (ch[x][i])
      mn[x] = min(mn[x], mn[ch[x][i]]);
  }
  void down(int x) {
    if (rev[x])
      rev[x] = 0, reverse(ch[x][0]), reverse(ch[x][1]);
  }
  void rotate(int x) {
    int y = fa[x], k = (ch[y][0] == x);
    ch[y][!k] = ch[x][k];
    fa[ch[x][k]] = y, fa[x] = fa[y];
    fa[ch[x][k] = y] = x;
    if (rt[y])
      rt[y] = false, rt[x] = true;
    else
      ch[fa[x]][ch[fa[x]][1] == y] = x;
    up(y);
  }
  void update(int x) {
    int top = 0;
    que[top++] = x;
    while (!rt[x]) x = fa[x], que[top++] = x;
    while (top) down(que[--top]);
  }
  void splay(int x) {
    update(x);
    while (!rt[x]) {
      int y = fa[x], z = fa[y];
      if (!rt[y])
        (ch[z][1] == y) == (ch[y][1] == x) ? rotate(y) : rotate(x);
      rotate(x);
    }
    up(x);
  }
  // x->root be a preferred path, like heavy chain
  void access(int x) {
    for (int y = 0; x; y = x, x = fa[x]) {
      splay(x);
      rt[ch[x][1]] = true;
      rt[ch[x][1] = y] = false;
      up(x);
    }
  }
  int getRoot(int x) {
    access(x), splay(x);
    while (ch[x][0]) x = ch[x][0];
    return x;
  }
  // make x be tree root
  void makeRoot(int x) {
    access(x), splay(x), reverse(x);
  }
  // be sure x,y not in one tree
  void addEdge(int x, int y) {
    makeRoot(x), fa[x] = y;
  }
  void delNode(int x) {
    splay(x);
    rep(i, 0, 2) {
      if (!ch[x][i]) continue;
      fa[ch[x][i]] = fa[x], rt[ch[x][i]] = true;
      fa[x] = ch[x][i] = 0;
    }
  }
} lct;


int Pow(ll a,ll b=P-2) {ll r=1;for(;b;b>>=1,a=a*a%P)if(b&1)r=r*a%P;return r;}
struct edge{
  int w,u,v;
  bool operator < (const edge&b) const{
    return w < b.w;
  }
}e[M];
vector<tuple<ll,ll,ll> > info;
int n , m , fa[N] , ban[M];
inline int F(int x){return fa[x] == x ? fa[x] : fa[x] = F(fa[x]);}

int main(){
    int tcas; scanf("%d", &tcas);
    rep(cas, 0, tcas) {
        scanf("%d%d",&n,&m);
        memset(ban , -1 , sizeof(int) * m);
        info.clear();
        rep(i,0,m){
          int u , v , w;
          scanf("%d%d%d",&u,&v,&w);
          --u;--v;
          e[i] = edge{w,u,v};
        }
        sort(e , e + m);
        lct.init(n + m);
        rep(i, 0, m) {
          int w = e[i].w, u = e[i].u + 1, v = e[i].v + 1;
          int b = n + i + 1;
          if (lct.getRoot(u) != lct.getRoot(v)) { // no circle
            info.pb(make_tuple(-inf, w , ll(w) * w));
          } else {
            lct.makeRoot(u);
            lct.access(v);
            lct.splay(v);
            int l = lct.mn[v] - (n + 1);
            ban[l] = i, info.pb(make_tuple(w + e[l].w, w , ll(w) * w));
            lct.delNode(lct.mn[v]);
          }
          lct.val[b] = b, lct.val[u] = lct.val[v] = INT_MAX;
          lct.addEdge(u, b), lct.addEdge(v, b);
        }
        rep(i,0,m) {
          int w=e[i].w;
          if(ban[i] == -1) info.pb(make_tuple(inf , ~w , ll(-w) * w));
          else info.pb(make_tuple(w + e[ban[i]].w , ~w , ll(-w) * w));
        }
        sort(all(info));
        int edgecnt = 0;
        // or use __int128
        ll high = 1e18 , low = 1e18 , sqsum = 0 , sum = 0;
        for(auto e : info) {
          ll a , b , c;
          tie(a , b , c) = e;
          if(b >= 0) edgecnt++;
          else edgecnt-- , b = -~b;
          sum += b;
          sqsum += c;
          if(edgecnt + 1 == n) {
            ll h = sqsum - (sum / (n - 1)) * sum - (sum % (n - 1)) * sum / (n - 1);
            ll l = - ((sum % (n - 1)) * sum % (n - 1));
            if(l < 0) l += n - 1 , h--;
            if(mp(high , low) > mp(h , l))
              high = h , low = l;
          }
        }
        printf("%d\n",int((high+low*Pow(n-1))%P*Pow(n-1)%P));
    }
    return 0;
}

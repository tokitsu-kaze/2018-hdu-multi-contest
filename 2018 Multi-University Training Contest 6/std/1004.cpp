#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define de(x) cout << #x << "=" << x << endl
#define rep(i,a,b) for(int i=a;i<b;++i)
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define fi first
#define se second

const int N = 605;
int T, n;
int H[N], L[N], R[N], W[N];

struct P {
    int x, y;
    P() {}
    P(int x, int y) : x(x), y(y) {}
    bool operator == (const P& c) const {
        return 1ll * x * c.y - 1ll * y * c.x == 0;
    }
    bool operator < (const P& c) const {
        return 1ll * x * c.y - 1ll * y * c.x < 0;
    }
} p[N];
int hn;

int find(P x) {
    return lower_bound(p + 1, p + 1 + hn, x) - p;
}

ll dp[N][N];
int Li[N], Ri[N];

int main() {
    //freopen("xx.in", "r", stdin);
        scanf("%d", &T);
        while (T--) {
            scanf("%d", &n);
            for (int i = 1; i <= n; i++) {
                scanf("%d%d%d%d", &H[i], &L[i], &R[i], &W[i]);
                p[i * 2 - 1] = P(L[i], H[i]);
                p[i * 2] = P(R[i], H[i]);
            }
            sort(p + 1, p + n * 2 + 1);
            hn = unique(p + 1, p + n * 2 + 1) - p - 1;
            for (int i = 1; i <= n; i++) {
                Li[i] = find(P(L[i], H[i]));
                Ri[i] = find(P(R[i], H[i]));
            }
            for (int len = 1; len <= hn; len++) {
                for (int l = 1; l + len - 1 <= hn; l++) {
                    int r = l + len - 1;
                    dp[l][r] = (1ll<<60);
                    int mx = -1, mv;
                    for (int k = 1; k <= n; k++) {
                        if (l <= Li[k] && Ri[k] <= r) {
                            if (W[k] > mx){
                                mx = W[k];
                                mv = k;
                            }
                        }
                    }
                    //printf("%d %d %d %d %d\n",l, r, mv, Li[mv], Ri[mv]);
                    int s = Li[mv], e = Ri[mv];
                    if (mx == -1) dp[l][r] = 0;
                    else {
                        for (int k = s; k <= e; k++) dp[l][r] = min(dp[l][r], dp[l][k - 1] + dp[k + 1][r] + mx);
                    }
                    //printf("%d %d %lld\n", l, r, dp[l][r]);
                }
            }
            printf("%lld\n", dp[1][hn]);
        }
    return 0;
}

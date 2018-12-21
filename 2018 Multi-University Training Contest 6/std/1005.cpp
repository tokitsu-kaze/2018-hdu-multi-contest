#include<bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pw(x) (1ll << (x))
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl

//-----
const int N = 2e3 + 7;
char s[N][N];
int n, m1, m2;
int rl[N], rr[N], cl[N], cr[N];
pii v1[N * N], v2[N * 4];

int lf[N][N], up[N][N];
pii dp[N][N];
int ans, cnt;
pii gao() {
    rep(i, 1, n + 1) rep(j, 1, n + 1) lf[i][j] = s[i][j] == '0' ? j : lf[i][j - 1];
    rep(j, 1, n + 1) rep(i, 1, n + 1) up[i][j] = s[i][j] == '0' ? i : up[i - 1][j];
    //rep(i, 1, n + 1) rep(j, 1, n + 1) cout << s[i][j] << " \n"[j == n]; de("======");
    //rep(i, 1, n + 1) rep(j, 1, n + 1) cout << lf[i][j] << " \n"[j == n]; de("++++++");

    rep(i, 0, n + 1) dp[i][0] = dp[0][i] = {INT_MAX, 0};
    rep(i, 1, n + 1) {
        rep(j, 1, n + 1) {
            dp[i][j] = {min(dp[i - 1][j].fi, dp[i][j - 1].fi), 0};
            if (dp[i][j].fi == dp[i - 1][j].fi) dp[i][j].se += dp[i - 1][j].se;
            if (dp[i][j].fi == dp[i][j - 1].fi) dp[i][j].se += dp[i][j - 1].se;
            if (dp[i][j].fi == dp[i - 1][j - 1].fi) dp[i][j].se -= dp[i - 1][j - 1].se;
            if (dp[i][j].fi == INT_MAX && s[i][j] == '1') dp[i][j] = {i + j, 1};
        }
    }

    rep(i, 0, m1) {
        pii d = dp[up[v1[i].fi][v1[i].se]][lf[v1[i].fi][v1[i].se]];
        int tmp = d.fi;
        d.fi = v1[i].fi + v1[i].se - d.fi;
        if (ans < d.fi) tie(ans, cnt) = d;
        else if (ans == d.fi) cnt += d.se;
    }
}

void reversei() {
    rep(j, 1, n + 1)
        for (int i = 1; i < n + 1 - i; i++) swap(s[i][j], s[n + 1 - i][j]);
    rep(i, 0, m1) v1[i].fi = n + 1 - v1[i].fi;
}

void reversej() {
    rep(i, 1, n + 1) reverse(s[i] + 1, s[i] + 1 + n);
    rep(i, 0, m1) v1[i].se = n + 1 - v1[i].se;
}


void solve() {
    rep(i, 1, n + 1) scanf(" %s", s[i] + 1);
    rep(i, 1, n + 1) {
        rl[i] = 1; while (rl[i] <= n && s[i][rl[i]] == '0') rl[i]++;
        rr[i] = n; while (rr[i] >= 1 && s[i][rr[i]] == '0') rr[i]--;
    }
    rep(j, 1, n + 1) {
        cl[j] = 1; while (cl[j] <= n && s[cl[j]][j] == '0') cl[j]++;
        cr[j] = n; while (cr[j] >= 1 && s[cr[j]][j] == '0') cr[j]--;
    }
    m1 = m2 = 0;
    rep(i, 1, n + 1) rep(j, 1, n + 1) if (s[i][j] == '1') {
        if (rl[i] < j && j < rr[i] && cl[j] < i && i < cr[j])
            v1[m1++] = {i, j};
        else
            v2[m2++] = {i, j};
    }

    //cnt v2
    ans = -INT_MAX, cnt = 0;
    gao();
    int tmp;
    rep(i, 0, m2) rep(j, i + 1, m2) if (v2[j].se < v2[i].se) {
        if (up[v2[j].fi][v2[j].se] >= v2[i].fi || lf[v2[i].fi][v2[i].se] >= v2[j].se)
            if (up[v2[j].fi][v2[i].se] >= v2[i].fi || lf[v2[j].fi][v2[i].se] >= v2[j].se)
                if (ans < (tmp  = v2[j].fi - v2[i].fi + v2[i].se - v2[j].se))
                    ans = tmp, cnt = 1;
                else  if (ans == tmp) cnt++;
    }
    else {
        if (up[v2[j].fi][v2[j].se] >= v2[i].fi || lf[v2[i].fi][v2[j].se] >= v2[i].se)
            if (up[v2[j].fi][v2[i].se] >= v2[i].fi || lf[v2[j].fi][v2[j].se] >= v2[i].se)
                if (ans < (tmp = v2[j].fi - v2[i].fi + v2[j].se - v2[i].se))
                    ans = tmp, cnt = 1;
                else if (ans == tmp) cnt++;
    }

    //cnt v1
    reversei(); gao();
    reversej(); gao();
    reversei(); gao();

    if (ans <= 0) puts("Opps!");
    else printf("%d %d\n", ans, cnt);

}

int main() {
    int tcas; scanf("%d", &tcas);
    rep(cas, 0, tcas) {
        scanf("%d", &n);
        solve();
    }
    return 0;
}

#include <bits/stdc++.h>
#define rep(i,m,n) for(i=m;i<=n;i++)
#define rsp(it,s) for(set<int>::iterator it=s.begin();it!=s.end();it++)
#define mod 1000000007
#define inf 0x3f3f3f3f
#define vi vector<int>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
#define pi acos(-1.0)
#define pii pair<int,int>
#define Lson L, mid, rt<<1
#define Rson mid+1, R, rt<<1|1
const int maxn = 1e5 + 10;
using namespace std;
int n, m, k, t, h[maxn], tot, ans[maxn];
set<int>comp[maxn];
struct node
{
        int to, nxt, com;
} e[maxn << 2];
void add(int x, int y, int z)
{
        tot++;
        e[tot].to = y;
        e[tot].com = z;
        e[tot].nxt = h[x];
        h[x] = tot;
}
priority_queue<pair<int, int> >p;
int main()
{
        int i, j;
        while (scanf("%d %d", &n, &m) == 2)
        {
                //cout << n << " " << m << endl;
                for (int i = 1; i <= n; i++)
                {
                        h[i] = 0;
                        ans[i] = inf;
                        comp[i].clear();
                }
                tot = 0;
                while (m--)
                {
                        int a, b, c;
                        scanf("%d%d%d", &a, &b, &c);
                        add(a, b, c);
                        add(b, a, c);
                }
                p.push({0, 1});
                ans[1] = 0;
                while (!p.empty())
                {
                        int now = p.top().se, ca = -p.top().fi;
                        p.pop();
                        if (ans[now] < ca)
                        {
                                continue;
                        }
                        for (i = h[now]; i; i = e[i].nxt)
                        {
                                int to = e[i].to, to_com = e[i].com;
                                int to_ca = ca + (!comp[now].count(to_com));
                                if (ans[to] > to_ca)
                                {
                                        ans[to] = to_ca;
                                        p.push({ -to_ca, to});
                                        comp[to].clear();
                                        comp[to].insert(to_com);
                                }
                                else if (ans[to] == to_ca)
                                {
                                        comp[to].insert(to_com);
                                }
                        }
                }
                printf("%d\n", ans[n] == inf ? -1 : ans[n]);
        }
        //system("Pause");
        return 0;
}

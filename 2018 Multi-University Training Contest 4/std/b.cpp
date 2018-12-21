#include <bits/stdc++.h>
using namespace std;

const int N = 200000;
const int MOD = 1000000007;
struct query
{
    int n, k, i;
} Q[N];
int T;
vector <query> lst[N];
int cnt, mx, chunk;
int fac[N], inv[N], res[N], in_chunk[N];
int powi(int a, int b)
{
    int c = 1;
    for (; b; b >>= 1, a = 1ll * a * a % MOD)
        if (b & 1) c = 1ll * c * a % MOD;
    return c;
}
int C(int a, int b)
{
    return 1ll * fac[a] * inv[b] % MOD * inv[a - b] % MOD;
}
int comp(query a, query b)
{
    return a.n < b.n;
}
int main()
{
    mx = 100000;
    fac[0] = 1; for (int i = 1; i <= mx; ++ i) fac[i] = 1ll * fac[i - 1] * i % MOD;
    inv[mx] = powi(fac[mx], MOD - 2); for (int i = mx - 1; ~i; -- i) inv[i] = 1ll * inv[i + 1] * (i + 1) % MOD;
    chunk = sqrt(mx);
    cnt = 1;
    for (int i = 1; i <= mx; i += chunk, ++ cnt)
        for (int j = i; j < i + chunk && j <= mx; ++ j)
            in_chunk[j] = cnt;
    cnt --;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++ i)
    {
        scanf("%d%d", &Q[i].n, &Q[i].k), Q[i].i = i;
        lst[in_chunk[Q[i].k]].push_back(Q[i]);
    }
    for (int i = 1; i <= cnt; ++ i) if (lst[i].size())
    {
        sort(lst[i].begin(), lst[i].end(), comp);
        int val = 0, in = lst[i][0].n, ik = -1;
        for (int j = 0; j < lst[i].size(); ++ j)
        {
            while (in < lst[i][j].n) val = (0ll + val + val + MOD - C(in ++, ik)) % MOD;
            while (ik < lst[i][j].k) val = (val + C(in, ++ ik)) % MOD;
            while (ik > lst[i][j].k) val = (val + MOD - C(in, ik --)) % MOD;
            res[lst[i][j].i] = val;
        }
    }
    for (int i = 1; i <= T; ++ i) printf("%d\n", res[i]);
}

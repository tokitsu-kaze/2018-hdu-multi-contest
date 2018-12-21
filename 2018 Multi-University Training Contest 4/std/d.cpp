#include <bits/stdc++.h>
using namespace std;
const int N = 500000;
int n, m;
int ai[N];
void solve()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i)
        scanf("%*d%d", &ai[i]);
    sort(ai + 1, ai + n + 1);
    for (int i = 1, j = 1; i <= n + 1; ++ i)
        if (i == n + 1 || 1ll * j * (ai[i] + 1) > m)
        {
            printf("%d\n", i - 1);
            break;
        }
        else j *= (ai[i] + 1);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T --) solve();
}

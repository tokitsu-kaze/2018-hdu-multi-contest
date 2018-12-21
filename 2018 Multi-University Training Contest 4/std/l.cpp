#include <bits/stdc++.h>
using namespace std;

void solve () {
    int n, a; cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        if (i == 1) a = x;
        if (i == n) cout << (int)sqrt(fabs(x - a) + 1e-3) << endl;
    }
}

int main () {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}

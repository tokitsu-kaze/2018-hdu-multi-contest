#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int A[10], M[400][400];
int L;

LL calc (int n, int m) {
    if (n < 0 || m < 0) return 0;
    return 1LL * M[L - 1][L - 1] * (n / L) * (m / L) + \
           1LL * M[n % L][L - 1] * (m / L) + \
           1LL * M[L - 1][m % L] * (n / L) + \
           1LL * M[n % L][m % L];
}

void solve () {
    cin >> L;
    for (int i = 0; i < L; ++i) cin >> A[i];
    int k = 0;
    for (int i = 0; i < 4 * L; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j < 2 * L && i - j < 2 * L) M[j][i - j] = A[k];
            k = (k + 1) % L;
        }
    }
    L *= 2;
    for (int i = 0; i < L; ++i) for (int j = 0; j < L; ++j) {
        if (i) M[i][j] += M[i - 1][j];
        if (j) M[i][j] += M[i][j - 1];
        if (i && j) M[i][j] -= M[i - 1][j - 1];
    }
    int Q; cin >> Q;
    while (Q--) {
        int xL, yL, xR, yR;
        cin >> xL >> yL >> xR >> yR;
        cout << calc(xR, yR) - calc(xL - 1, yR) - calc(xR, yL - 1) + calc(xL - 1, yL - 1) << endl;
    }
}

int main () {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}

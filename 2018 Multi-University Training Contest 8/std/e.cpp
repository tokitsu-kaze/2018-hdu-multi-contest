#include <bits/stdc++.h>
using namespace std;

char grid[4][4];

array<char*, 4> submat[] = {
    { &grid[0][0], &grid[0][1], &grid[1][1], &grid[1][0] },
    { &grid[0][1], &grid[0][2], &grid[1][2], &grid[1][1] },
    { &grid[1][0], &grid[1][1], &grid[2][1], &grid[2][0] },
    { &grid[1][1], &grid[1][2], &grid[2][2], &grid[2][1] }
};

void rot(array<char*, 4>& a, bool cw) {
    char temp;
    if (!cw) {
        temp = *(a[0]);
        *(a[0]) = *(a[1]);
        *(a[1]) = *(a[2]);
        *(a[2]) = *(a[3]);
        *(a[3]) = temp;
    } else {
        temp = *(a[3]);
        *(a[3]) = *(a[2]);
        *(a[2]) = *(a[1]);
        *(a[1]) = *(a[0]);
        *(a[0]) = temp;
    }
}

int main() {
    int T; cin >> T;
    int n;
    while (T--) {
        cin >> n;
        for (int i = 0; i < 3; i++) cin >> grid[i];
        while (n--) {
            string op; cin >> op;
            rot(submat[op[0]-'1'], op[1] == 'C');
        }
        for (int i = 0; i < 3; i++) cout << grid[i] << endl;
    }
    return 0;
}

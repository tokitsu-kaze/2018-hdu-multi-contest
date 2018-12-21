#include <bits/stdc++.h>
using namespace std;

int k;
string a, b, c, d;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> k >> a >> b;
        assert(a.length() >= 1 && a.length() <= 200000);
        assert(b.length() >= 1 && b.length() <= 200000);
        if (k <= 2) {
            cout << (a == b ? "yes" : "no") << endl;
        } else if (k == 3) {
            a.resize(unique(a.begin(), a.end()) - a.begin());
            b.resize(unique(b.begin(), b.end()) - b.begin());
            cout << (a == b ? "yes" : "no") << endl;
        } else if (k == 4) {
            c.clear(); d.clear();
            a.resize(unique(a.begin(), a.end()) - a.begin());
            b.resize(unique(b.begin(), b.end()) - b.begin());
            for (char ch : a) {
                c.push_back(ch);
                if (c.size() >= 3 && c.rbegin()[0] == c.rbegin()[2])
                    c.resize(c.size() - 2);
            }
            for (char ch : b) {
                d.push_back(ch);
                if (d.size() >= 3 && d.rbegin()[0] == d.rbegin()[2])
                    d.resize(d.size() - 2);
            }
            cout << (c == d ? "yes" : "no") << endl;
        } else {
            cout << (*a.begin() == *b.begin() && *a.rbegin() == *b.rbegin() ?
                     "yes" : "no") << endl;
        }
    }
    return 0;
}

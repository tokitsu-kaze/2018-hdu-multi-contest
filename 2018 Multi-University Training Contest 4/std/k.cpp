#include <bits/stdc++.h>
using namespace std;

int T; string res;
int main()
{
    ios :: sync_with_stdio(0);
    cin >> T;
    while (T --)
    {
        cin >> res;
        int flag = 1;
        for (int i = 1; i < res.size(); ++ i)
            if (res[i] == '?' && res[i - 1] == '0' && (i == 1 || res[i - 2] == '+' || res[i - 2] == '*'))
                res[i] = '+';
        for (int i = 0; i < res.size(); ++ i)
            if (res[i] == '?') res[i] = '1';
        if (res[0] == '+' || res[0] == '*') flag = 0;
        if (res[res.size() - 1] == '+' || res[res.size() - 1] == '*') flag = 0;
        for (int i = 0; i < res.size() - 1; ++ i)
            if ((res[i] == '+' || res[i] == '*') && (res[i + 1] == '+' || res[i + 1] == '*'))
                flag = 0;
        for (int i = 0; i < res.size() - 1; ++ i)
            if ((i == 0 || res[i - 1] == '+' || res[i - 1] == '*') && (res[i] == '0') && (res[i + 1] != '+' && res[i + 1] != '*'))
                flag = 0;
        if (flag) cout << res << endl;
        else cout << "IMPOSSIBLE" << endl;
    }
}

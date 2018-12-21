#include <bits/stdc++.h>
using namespace std;

#define LL long long
const int N = 300000;
const int M = 5000000;
struct point
{
    int left, right, stamp, size;
    int rev; LL add, pos;
    int val, sum;
} tr[M];

int now, tot, key, n;
int rtL[N], rtR[N];

int check(int t)
{
    if (tr[t].stamp != now)
    {
        int p = ++ tot;
        tr[p] = tr[t];
        tr[p].stamp = now;
        return p;
    }
    else return t;
}
int upd(int t)
{
    if (!t) return 0;
    tr[t].sum = tr[tr[t].left].sum + tr[tr[t].right].sum + tr[t].val;
    tr[t].size = tr[tr[t].left].size + tr[tr[t].right].size + 1;
    return t;
}
int rev(int t)
{
    if (!t) return 0;
    t = check(t);
    tr[t].rev ^= 1;
    tr[t].add *= -1;
    tr[t].pos *= -1;
    swap(tr[t].left, tr[t].right);
    return t;
}
int add(int t, LL v)
{
    if (!t) return 0;
    t = check(t);
    tr[t].add += v;
    tr[t].pos += v;
    return t;
}
int psdw(int t)
{
    if (!t) return 0;
    t = check(t);
    if (tr[t].rev)
    {
        if (tr[t].left) tr[t].left = rev(tr[t].left);
        if (tr[t].right) tr[t].right = rev(tr[t].right);
        tr[t].rev = 0;
    }
    if (tr[t].add)
    {
        if (tr[t].left) tr[t].left = add(tr[t].left, tr[t].add);
        if (tr[t].right) tr[t].right = add(tr[t].right, tr[t].add);
        tr[t].add = 0;
    }
    return t;
}
void split(int t, LL p, int &l, int &r)
{
    if (!t) {l = r = 0; return;}
    t = psdw(t);
    if (p <= tr[t].pos)
    {
        split(tr[t].left, p, l, r);
        tr[t].left = r; r = upd(t);
    }
    else
    {
        split(tr[t].right, p, l, r);
        tr[t].right = l; l = upd(t);
    }
}
int merge(int a, int b)
{
    if (!a || !b) return a | b;
    if (1ll * rand() * (tr[a].size + tr[b].size) < 1ll * tr[a].size * RAND_MAX)
    {
        a = psdw(a); tr[a].right = merge(tr[a].right, b); return upd(a);
    }
    else
    {
        b = psdw(b); tr[b].left = merge(a, tr[b].left); return upd(b);
    }
}
void init(LL pos, int &l, int &r, int v)
{
    l = ++ tot; r = ++ tot;
    tr[l].stamp = tr[r].stamp = now;
    tr[l].pos = tr[r].pos = pos;
    tr[l].val = tr[r].val = v;
    upd(l); upd(r);
}
void solve(istream &in, ostream &os, int online = 1)
{
    for (int i = 1; i <= n; ++ i) rtL[i] = rtR[i] = 0;
    for (int i = 1; i <= tot; ++ i) tr[i] = tr[0]; key = tot = now = 0;
    in >> n;
    init(0, rtL[0], rtR[0], 1);
    for (int i = 1; i <= n; ++ i)
    {
        int opt; LL x, l, r; now = i;
        int Ll, Lr, Lm, Rl, Rr, Rm;
        in >> opt;
        rtL[i] = rtL[i - 1]; rtR[i] = rtR[i - 1];
        if (opt == 1)
        {
            in >> x; x ^= key;
            split(rtL[i], x, Ll, Lr);
            split(rtR[i], x, Rl, Rr);
            init(x, Lm, Rm, 1);
            rtL[i] = merge(merge(Ll, Lm), Lr);
            rtR[i] = merge(merge(Rl, Rm), Rr);
        }
        else if (opt == 2)
        {
            in >> x; x ^= key;
            rtL[i] = add(rtL[i], -x);
            rtR[i] = add(rtR[i], x);
        }
        else if (opt == 3)
        {
            in >> l >> r; l ^= key; r ^= key;
            split(rtL[i], l, Ll, Lr); split(Lr, r + 1, Lm, Lr);
            split(rtR[i], l, Rl, Rr); split(Rr, r + 1, Rm, Rr);
            int Lx, Ly, Rx, Ry;
            init(0, Lx, Ly, tr[Rr].sum - tr[Lr].sum);
            tr[Lx].pos = l; tr[Ly].pos = r + 1;
            init(0, Rx, Ry, tr[Ll].sum - tr[Rl].sum);
            tr[Rx].pos = l - 1; tr[Ry].pos = r;
            rtL[i] = merge(merge(merge(Ll, Lx), add(rev(Rm), l + r)), merge(Ly, Lr));
            rtR[i] = merge(merge(merge(Rl, Rx), add(rev(Lm), l + r)), merge(Ry, Rr));
        }
        else if (opt == 4)
        {
            in >> x; x ^= key;
            rtL[i] = rtL[x]; rtR[i] = rtR[x];
        }
        else
        {
            in >> x; x ^= key;
            split(rtL[i], x + 1, Ll, Lr);
            split(rtR[i], x, Rl, Rr);
            if (tr[Ll].sum ^ tr[Rl].sum)
                os << "Yes" << endl, key += online;
                else os << "No" << endl;
            rtL[i] = rtL[i - 1]; rtR[i] = rtR[i - 1];
        }
    }
    // cerr << key << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    int T;
    for (cin >> T; T; T --) solve(cin, cout);
}

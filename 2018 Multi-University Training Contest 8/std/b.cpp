#include <bits/stdc++.h>
using namespace std;

typedef complex<double> pt;

bool cmp(pt a, pt b) {
    return make_pair(a.real(), a.imag()) < make_pair(b.real(), b.imag());
}

const double eps = 1e-9;
int w;

double test(pt v1, pt v2) {
    if (norm(v1) <= w * w) {
        v2 /= v1 / abs(v1);
        if (v2.imag() > -eps && v2.real() > -eps && v2.real() < w + eps) {
            return v2.imag();
        } else {
            return DBL_MAX;
        }
    } else {
        double h = sqrt(norm(v1) - w * w);
        double a = atan(h / w), a2 = arg(v1);
        v1 = polar(abs(v1), a);
        v2 *= polar(1.0, a - a2);
        if (v2.imag() > -eps && v2.real() > -eps && v2.real() < w + eps) {
            return max(v1.imag(), v2.imag());
        } else {
            return DBL_MAX;
        }
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int x1, y1, x2, y2, x3, y3;
        scanf("%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &w);
        pt pts[3] = {pt(x1, y1), pt(x2, y2), pt(x3, y3)};
        sort(pts, pts+3, cmp);
        double value = DBL_MAX;
        do {
            value = min(value, test(pts[1] - pts[0], pts[2] - pts[0]));
        } while (next_permutation(pts, pts+3, cmp));
        for (int i = 0; i < 3; i++) pts[i] = conj(pts[i]);
        sort(pts, pts+3, cmp);
        do {
            value = min(value, test(pts[1] - pts[0], pts[2] - pts[0]));
        } while (next_permutation(pts, pts+3, cmp));
        if (value == DBL_MAX) puts("impossible");
        else printf("%.12f\n", value);
    }
    return 0;
}

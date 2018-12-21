#include<bits/stdc++.h>
using namespace std;

namespace fastIO {
	#define BUF_SIZE 100000
	//fread -> read
	bool IOerror = 0;
	inline char nc() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) {
				IOerror = 1;
				return -1;
			}
		}
		return *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	inline void read(int &x) {
		char ch;
		while(blank(ch = nc()));
		if(IOerror) return;
		for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
	}
	#undef BUF_SIZE
};
using namespace fastIO;


const int N = 200010, M = 15;

pair<int, int> a[M][N];
int b[N][M];
int v[M], point[M], cnt[N], n, m;

int main() {
//	freopen("swordman.in", "r", stdin);
//	freopen("swordman.out", "w", stdout);
	int T; read(T);
	while (T--) {
		read(n); read(m);
		for (int i = 1; i <= m; ++i) read(v[i]);
		memset(point, 0, sizeof(point));
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				read(a[j][i].first);
				a[j][i].second = i;
			}
			for (int j = 1; j <= m; ++j)
				read(b[i][j]);
			cnt[i] = 0;
		}
		int ans = 0;
		for (int i = 1; i <= m; ++i)
			sort(a[i] + 1, a[i] + n + 1);
		while (1) {
			int oldans = ans;
			for (int i = 1; i <= m; ++i) {
				while (point[i] < n && a[i][point[i] + 1].first <= v[i]) {
					int x = a[i][++point[i]].second;
					cnt[x]++;
					if (cnt[x] == m) {
						++ans;
						for (int j = 1; j <= m; ++j)
							v[j] += b[x][j];
					}
				}
			}
			if (oldans == ans) break;
		}
		printf("%d\n", ans);
		for (int i = 1; i < m; ++i)
			printf("%d ", v[i]);
		printf("%d\n", v[m]);
	}
	return 0;
}

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
typedef pair<int, int> pp;
typedef priority_queue< pp, vector<pp>, greater<pp> > QQ;
QQ q[M];
int n, m, a[N][M], b[N][M], v[M];

int main() {
//	freopen("swordman.in", "r", stdin);
//	freopen("swordman.out", "w", stdout);
	int T; read(T);
	while (T--) {
		read(n); read(m);
		for (int i = 1; i <= m; ++i) read(v[i]);
		for (int i = 1; i <= m; ++i)
			q[i] = QQ();
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j)
				read(a[i][j]);
			q[1].push({a[i][1], i});
			for (int j = 1; j <= m; ++j)
				read(b[i][j]);
		}
		
		int ans = 0;
		while (1) {
			int oldans = ans;
			
			for (int i = 1; i < m; ++i) {
				while (!q[i].empty() && q[i].top().first <= v[i]) {
					int x = q[i].top().second;
					q[i].pop();
					q[i + 1].push({a[x][i + 1], x});
				}
			}
			while (!q[m].empty() && q[m].top().first <= v[m]) {
				int x = q[m].top().second;
				q[m].pop();
				++ans;
				for (int i = 1; i <= m; ++i)
					v[i] += b[x][i];
			}
			
			if (ans == oldans) break;
		}
		
		printf("%d\n", ans);
		for (int i = 1; i < m; ++i)
			printf("%d ", v[i]);
		printf("%d\n", v[m]);
	}
	
	return 0;
}

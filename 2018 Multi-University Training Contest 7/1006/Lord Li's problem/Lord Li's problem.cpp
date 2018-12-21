#include<bits/stdc++.h> 
using namespace std;
int n, k, kase;
char S[50], T[50];
int cnt;
long long C[50][50], d[30][45];
const long long mod = 19260817;
long long inv[55];
long long fpow(long long a, long long m)
{
	long long ret = 1;
	while (m) {
		if (m & 1)ret = ret * a%mod;
		a = a * a%mod;
		m >>= 1;
	}
	return ret;
}
void init()
{
	C[0][0] = 1;
	for (int i = 1; i < 50; i++) {
		C[i][0] = C[i][i] = 1;
		for (int j = 0; j < i; j++) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
		}
	}
	for (int i = 1; i <= 50; i++)inv[i] = fpow(i, mod - 2);
}
int main()
{
	init();
	while (scanf("%d%d", &n, &k) == 2 && n) {
		cnt = 0;
		scanf("%s", S);
		scanf("%s", T);
		for (int i = 0; i < n; i++) {
			cnt += (S[i]-'0') ^ (T[i]-'0');
		}
		d[0][0] = 1;
		for (int i = 1; i <= k; i++) {
			for (int j = 0; j <= n; j++) {
				d[i][j] = 0;
				if (j + 1 <= n)d[i][j] = (d[i][j] + d[i - 1][j + 1] * C[j][1] * C[n - j][2]) % mod;
				if (j + 3 <= n)d[i][j] = (d[i - 1][j + 3] * C[n-j][3] + d[i][j]) % mod;
				if (j >= 1)d[i][j] = (d[i][j] + d[i - 1][j - 1] * C[j][2] * C[n - j][1]) % mod;
				if (j >= 3)d[i][j] = (d[i][j] + d[i - 1][j - 3] * C[j][3]) % mod;
				if (i - 2 >= 0)d[i][j] = (d[i][j] - (d[i - 2][j] * (C[n][3] - i + 2))) % mod;
				d[i][j] = d[i][j] * inv[i] % mod;
				d[i][j] = (d[i][j] + mod) % mod;
			}
		}
		printf("Case #%d: %lld\n",++kase, d[k][cnt]);
	}
}
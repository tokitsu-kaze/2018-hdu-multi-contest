#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
const int INF=1e9+1;

int T,n,dp[maxn][2],A[maxn],B[maxn];
bool num[maxn];

int main()
{
	int i;
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		for (i=0;i<=n+5;i++)
		{
			A[i]=B[i]=num[i]=0;
			dp[i][0]=dp[i][1]=INF;
		}
		char c=getchar();
		while (c!='0'&&c!='1') c=getchar();
		for (i=1;i<=n;i++)
			num[i]=c=='1',c=getchar();
		A[0]=INF;
		while (c!='0'&&c!='1') c=getchar();
		for (i=1;i<=n;i++,c=getchar())
			A[i]=c=='0'?1:min(A[i-1]*2,INF);
		B[0]=INF;
		while (c!='0'&&c!='1') c=getchar();
		for (i=1;i<=n;i++,c=getchar())
			B[i]=c=='0'?1:min(B[i-1]*2,INF);
		A[n+1]=B[n+1]=1;

		dp[0][0]=0;
		for (i=1;i<=n+1;i++)
		{
			if (num[i])
			{
				dp[i][0]=min(dp[i][0],dp[i-1][0]+A[i]);
				dp[i][1]=min(dp[i][1],dp[i-1][0]+B[i]);
				dp[i][1]=min(dp[i][1],dp[i-1][1]);
			}
			else
			{
				dp[i][0]=min(dp[i][0],dp[i-1][0]);
				dp[i][0]=min(dp[i][0],dp[i-1][1]+A[i]);
				dp[i][1]=min(dp[i][1],dp[i-1][1]+B[i]);
			}
		}
		if (dp[n+1][0]==INF) puts("-1");
		else printf("%d\n",dp[n+1][0]);
	}
}


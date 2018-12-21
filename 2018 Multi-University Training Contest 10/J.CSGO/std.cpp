#include<bits/stdc++.h>
using namespace std;
#define LL long long

int T,n,m,K,val,x[6];
LL A[64],B[64],Ans;

int main()
{
	int i,k,S;
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d%d",&n,&m,&K);
		Ans=0;
		memset(A,0,sizeof(A));
		memset(B,0,sizeof(B));

		for (i=1;i<=n;i++)
		{
			scanf("%d",&val);
			for (k=0;k<K;k++)
				scanf("%d",&x[k]);
			for (S=0;S<1<<K;S++)
			{
				LL Sum=val;
				for (k=0;k<K;k++)
					Sum+=x[k]*((((S>>k)&1)<<1)-1);
				A[S]=max(A[S],Sum);
			}
		}

		for (i=1;i<=m;i++)
		{
			scanf("%d",&val);
			for (k=0;k<K;k++)
				scanf("%d",&x[k]);
			for (S=0;S<1<<K;S++)
			{
				LL Sum=val;
				for (k=0;k<K;k++)
					Sum+=x[k]*((((S>>k)&1)<<1)-1);
				B[S]=max(B[S],Sum);
			}
		}

		for (S=0;S<1<<K;S++)
			Ans=max(Ans,A[S]+B[(1<<K)-1-S]);
		printf("%lld\n",Ans);
	}
}


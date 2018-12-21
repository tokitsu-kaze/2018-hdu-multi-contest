#include<bits/stdc++.h>
using namespace std;
#define LL long long

const int N=2e7;
const int maxn=N+10;

int T,n;
int primes,prime[maxn],phi[maxn];
bool vis[maxn];
LL Ans[maxn];

void init()
{
	int i,j;
	phi[1]=1;
	for (i=2;i<=N;i++)
	{
		if (!vis[i])
		{
			prime[++primes]=i;
			phi[i]=i-1;
		}
		for (j=1;j<=primes&&i*prime[j]<=N;j++)
		{
			vis[i*prime[j]]=1;
			if (i%prime[j])
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
			else
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
		}
	}
	LL Sum=0;
	for (i=1;i<=N;i++)
		Sum+=phi[i],Ans[i]=Ans[i>>1]+Sum;
}

int main()
{
	init();
	scanf("%d",&T);
	while (T--)
		scanf("%d",&n),printf("%lld\n",Ans[n]>>1);
}


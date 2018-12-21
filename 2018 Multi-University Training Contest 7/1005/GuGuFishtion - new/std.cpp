#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+100;
typedef long long ll;
int fac[maxn],miu[maxn],phi[maxn];//f[maxn],F[maxn];
ll f[maxn],F[maxn];
void init()
{
    for(int i=1;i<maxn;++i) fac[i]=i;
    phi[1]=miu[1]=1;
    for(int i=2;i<maxn;++i)
    {
        if(fac[i]==i)
            for(int j=i<<1;j<maxn;j+=i)
                fac[j]=i;
        if(i/fac[i]%fac[i]) phi[i]=(fac[i]-1)*phi[i/fac[i]],miu[i]=-miu[i/fac[i]];
        else phi[i]=fac[i]*phi[i/fac[i]],miu[i]=0;
    }
}
ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)    return (x=1,y=0,a);
    if(a==0)    return (x=0,y=1,b);
    ll r=exgcd(b,a%b,y,x);
    y-=(a/b)*x;
    return r;
}
int mul_1(ll a,ll b)
{
    ll x,y;
    exgcd(a,b,x,y);
    x%=b;
    while(x<0)  x+=b;
    return x;
}
void Mobius(int m,int n,int MOD)
{
    int N=min(m,n);
    for(int i=1;i<=N;++i)   F[i]=1ll*(m/i)*(n/i);
    for(int i=1;i<=N;++i)
        for(int j=i;j<=N;j+=i)
            f[i]+=1ll*miu[j/i]*F[j];
    for(int i=1;i<=N;++i)   f[i]%=MOD;
}
int solve(int m,int n,int MOD)
{
    memset(f,0,sizeof f);
    memset(F,0,sizeof F);
    Mobius(m,n,MOD);
    int N=min(m,n);
    int ans=0;
    for(int i=1;i<=N;++i)
        ans=(1ll*ans+1ll*i*mul_1(phi[i],MOD)%MOD*f[i])%MOD;
    while(ans<0)    ans+=MOD;
    return ans;
}
int main()
{
    init();
    int T,m,n,p;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&m,&n,&p);
        printf("%d\n",solve(m,n,p));
    }
    return 0;
}

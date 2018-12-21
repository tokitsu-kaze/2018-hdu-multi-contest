nclude <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
const int mo=998244353;
long long n;
const int N=1000000,M=710000;
int prime[N+10],pd[N+10],len,sump[N+10],miu[N+10],h[N+10];
int f[M],m,lim[M],pre[M];
long long v[M];
int getid(long long k){
    if (k<=m) return k; return n/k+m;
}
int getvalue(long long k1,int R){
    int where=getid(k1);// cout<<k1<<" "<<where<<endl;
    int now=f[where],l=pre[where],r=min(R,lim[where]);
    if (l<r) now=(now-(sump[r]-sump[l]+mo)%mo+mo)%mo;
    return now;
}
int getsum(long long n){
    m=1; while (1ll*m*m<=n) m++; --m;
    for (int i=1;i<=m;i++) f[i]=1ll*i*(i+1)/2%mo,v[i]=i;
    for (int i=1;i<=m;i++){
        int now=n/i%mo; f[i+m]=1ll*now*(now+1)/2%mo; v[i+m]=n/i;
    }
    for (int i=1;i<=m*2;i++) pre[i]=0;
    for (int i=1;i<=m;i++) lim[i]=pd[i];
    for (int i=m+1;i<=m*2;i++) lim[i]=len;
    int la=0;
    for (int i=1;i<=len&&prime[i]<=m;i++){
        int lim=m,s=0; long long K=1ll*prime[i]*prime[i]; la=i;
        for (int j=m+1;j<=2*m&&v[j]>=K;j++)
            f[j]=(f[j]-1ll*prime[i]*getvalue(v[j]/prime[i],i-1)%mo+mo)%mo,pre[j]=i;
        for (int j=m;j&&v[j]>=K;j--)
            f[j]=(f[j]-1ll*prime[i]*getvalue(v[j]/prime[i],i-1)%mo+mo)%mo,pre[j]=i;
    }
    return la;
}
int forceget(int k1,int k2){
    vector<int>A;
    if (k1==k2) return 0;
    int k=k1; int ans=0;
    for (int i=2;i*i<=k;i++)
        if (k%i==0){
            A.push_back(i);
            while (k%i==0) k/=i;
        }
    if (k>1) A.push_back(k);
    k=k2;
    for (int i=2;i*i<=k;i++)
        if (k%i==0){
            A.push_back(i);
            while (k%i==0) k/=i;
        }
    if (k>1) A.push_back(k);
    sort(A.begin(),A.end());
    A.resize(unique(A.begin(),A.end())-A.begin());
    for (int i=0;i<A.size();i++){
        int num=0;
        while (k1%A[i]==0){
            num^=1; k1/=A[i];
        }
        while (k2%A[i]==0){
            num^=1; k2/=A[i];
        }
        if (num) ans+=A[i];
    }
    if (ans==0) return 1; else return ans;
}    
int getmiu(long long n){
    if (n<=N) return h[n];
    int ans=0;
    for (int i=1;1ll*i*i<=n;i++)
        ans=(ans+miu[i]*(n/i/i))%mo;
    return (ans+mo)%mo;
}
int get(long long k){
    int num=trunc(sqrt(k));
    while (1ll*num*num<=k) num++;
    while (1ll*num*num>k) num--;
    return (1ll*num*(num-1)/2)%mo;
}
int ca=0;
void solve(){
    scanf("%lld",&n);
    assert(n<=1e10);
    if (n>1e8) ca++;
    /*int num=0,num1=0;
    for (int i=1;i<=n;i++)
        for (int j=i;j<=n;j++){
            int k1=forceget(i,j);
            num=(num+k1)%mo;
            if (k1>1) num1=(num1+k1)%mo;
        }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++) cout<<forceget(i,j)<<" ";
        cout<<endl;
    }
    cout<<num<<" "<<num1<<endl;*/
    int ans=0;
    int la=getsum(n);
    for (int i=1;i<=la;i++){
        long long now=1;
        int w1=0,w0=0,t=0;
        while (now<=n){
            if (t&1) w1=(w1+(n/now-n/now/prime[i]))%mo;
            else w0=(w0+(n/now-n/now/prime[i]))%mo;
            if (now>n/prime[i]) break;
            now*=prime[i]; 
            t++;
        }
        ans=(ans+1ll*w0*w1%mo*prime[i])%mo;
    }
    //cout<<"asd"<<endl;
    int presum=0;
    /*cout<<presum<<endl;
    for (int i=1;i<=10;i++) cout<<getvalue(i,la)<<" "; cout<<endl;
    for (int i=1;i<=10;i++) cout<<pre[i]<<" "; cout<<endl;
    for (int i=1;i<=10;i++) cout<<lim[i]<<" "; cout<<endl;
    for (int i=1;i<=10;i++) cout<<f[i]<<" "; cout<<endl;
    for (int i=1;i<=10;i++) cout<<getvalue(n/i,la)<<" "; cout<<endl;*/
    for (long long i=prime[la]+1,ne;i<=n;i=ne+1){
        ne=n/(n/i); int curp=getvalue(ne,la)-1;
        // cout<<i<<" "<<ne<<" "<<curp<<" "<<presum<<endl;
        int sum=(curp-presum+mo)%mo;
        int w=(n/i)%mo*((n-n/i)%mo)%mo;
        ans=(ans+1ll*sum*w)%mo;
        presum=curp;
    }
    // cout<<"presum "<<presum<<endl;
    int lim=1; while (1ll*lim*lim<=n) ++lim; lim--;
    int pre=0;
    for (long long i=1,ne;i<=n;i=ne+1){
        ne=n/(n/i); int w=get(n/i);
        int cur=getmiu(ne);
        ans=(ans+1ll*(cur-pre+mo)*w)%mo;
        pre=cur;
    }
    printf("%d\n",ans);
    // assert(ans==num);
}
int main(){
    pd[1]=1; miu[1]=1;
    for (int i=2;i<=N;i++){
        if (pd[i]==0) prime[++len]=i,miu[i]=-1;
        for (int j=1;j<=len&&prime[j]*i<=N;j++){
            int now=prime[j]*i; pd[now]=1; miu[now]=-miu[i];
            if (i%prime[j]==0){
                miu[now]=0; break;
            }
        }
    }
    for (int i=1;i<=len;i++) sump[i]=(sump[i-1]+prime[i])%mo;
    for (int i=1;i<=N;i++) h[i]=(h[i-1]+(miu[i]!=0));
    for (int i=1;i<=N;i++) pd[i]=pd[i-1]+1-pd[i];
    int t; scanf("%d",&t); assert(t<=50);
    for (;t;t--) solve(); assert(ca<=3);
    return 0;
}

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cassert>
using namespace std;
#define mp make_pair
#define fi first
#define se second
#define pb push_back
const int mo=998244353,N=610;
int x[N][N];
int quick(int k1,int k2){
    int k3=1;
    while (k2){
        if (k2&1) k3=1ll*k3*k1%mo;
        k1=1ll*k1*k1%mo; k2>>=1;
    }
    return k3;
}
int gauss(int n){
    n--;
    int flag=1;
    for (int i=1;i<=n;i++){
        int r=i;
        for (int j=i;j<=n;j++)
            if (x[j][i]) r=j;
        for (int j=1;j<=n;j++) swap(x[i][j],x[r][j]);
        if (r!=i) flag=-flag;
        flag=1ll*flag*x[i][i]%mo;
        int num=quick(x[i][i],mo-2);
        for (int j=1;j<=n;j++) x[i][j]=1ll*x[i][j]*num%mo;
        assert(x[i][i]==1);
        for (int j=i+1;j<=n;j++)
            if (x[j][i]){
                int k1=x[j][i];
                for (int k=1;k<=n;k++) x[j][k]=(x[j][k]-1ll*x[i][k]*k1)%mo;
            }
    }
    flag=(flag+mo)%mo;
    return flag;
}
int n,a[N],m,size[N],pre[N];
map<int,int>M[N];
pair<int,int> u[N],v[N];
pair<int,int> insert(int k1,int k2){
    if (M[k1][k2]==0){
        size[k1]++; M[k1][k2]=size[k1];
    }
    return mp(k1,M[k1][k2]);
}
pair<int,int> readpair(){
    int k3; scanf("%d",&k3); assert(k3>0);
    int k1=1;
    while (a[k1]<k3){
        k3-=a[k1]; k1++;
    }
    assert(k1<=n);
    int k2=k3;
    return insert(k1,k2);
}
int getid(int k1,int k2){
    if (a[k1]==size[k1]) return pre[k1-1]+k2;
    return pre[k1-1]+k2+1;
}
void link(pair<int,int> k1,pair<int,int> k2){
    int k3=getid(k1.fi,k1.se);
    int k4=getid(k2.fi,k2.se);
    x[k3][k3]=(x[k3][k3]+1)%mo;
    x[k3][k4]=(x[k3][k4]+mo-1)%mo;
    x[k4][k4]=(x[k4][k4]+1)%mo;
    x[k4][k3]=(x[k4][k3]+mo-1)%mo;
}
int force(){
    for (int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i],size[i]=a[i];
    memset(x,0x00,sizeof x);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=a[i];j++)
            for (int k=j+1;k<=a[i];k++)
                link(mp(i,j),mp(i,k));
    for (int i=1;i<=m;i++) link(u[i],v[i]);
    return gauss(pre[n]);
}
int father[N];
int ca=0;
int findfather(int k1){
    if (father[k1]==k1) return k1; return father[k1]=findfather(father[k1]);
}
void solve(){
    scanf("%d%d",&n,&m);
    assert(1<=n&&n<=200&&0<=m&&m<=200);
    if (max(n,m)>50) ca=1;
    for (int i=1;i<=n;i++) M[i].clear(),size[i]=0;
    for (int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        assert(a[i]>=1&&a[i]<=1000000);
        father[i]=i;
    }
    for (int i=1;i<=n;i++) father[i]=i;
    for (int i=1;i<=m;i++){
        u[i]=readpair(); v[i]=readpair();
    }
    /*for (int i=1;i<=n;i++) cerr<<size[i]<<" "; cerr<<endl;
    int bo=0;
    for (int i=1;i<=n;i++) if (a[i]!=size[i]) bo=1;
    if (bo==0) cerr<<"fa"<<endl;*/
    for (int i=1;i<=m;i++)
        father[findfather(u[i].fi)]=findfather(v[i].fi);
    for (int i=1;i<=n;i++) assert(findfather(1)==findfather(i));
    if (m==0){
        if (n==1) printf("%d\n",quick(a[1],a[1]-2));
        else printf("%d\n",0); return;
    }
    if (n>1){
        for (int i=1;i<=n;i++) if (size[i]==0){
            printf("0\n"); return;
        }
    }
    pre[0]=0; int ans=1;
    for (int i=1;i<=n;i++)
        if (size[i]==a[i]) pre[i]=pre[i-1]+size[i]; else pre[i]=pre[i-1]+1+size[i],ans=1ll*ans*quick(a[i],a[i]-size[i]-1)%mo;
    for (int i=0;i<=pre[n];i++)
        for (int j=0;j<=pre[n];j++) x[i][j]=0;
    for (int i=1;i<=n;i++)
        if (size[i]==a[i]){
            for (int j=1;j<=a[i];j++)
                for (int k=j+1;k<=a[i];k++)
                    link(mp(i,j),mp(i,k));
        } else {
            int o=getid(i,0);
            for (int j=1;j<=size[i];j++){
                int k1=getid(i,j);
                x[k1][o]=(x[k1][o]-a[i]+mo)%mo;
                x[k1][k1]=(x[k1][k1]+a[i])%mo;
                x[o][k1]=(x[o][k1]-1+mo)%mo;
            }
            x[o][o]=(x[o][o]+size[i])%mo;
        }
    for (int i=1;i<=m;i++) link(u[i],v[i]);
    /*cout<<ans<<endl;
    for (int i=1;i<=pre[n];i++){
        for (int j=1;j<=pre[n];j++) cout<<x[i][j]<<" "; cout<<endl;
    }*/
    ans=1ll*ans*gauss(pre[n])%mo;
    printf("%d\n",ans);
    // printf("%d\n",force());
}
int main(){
    int t; scanf("%d",&t);
    for (;t;t--) solve();
    return 0;
}

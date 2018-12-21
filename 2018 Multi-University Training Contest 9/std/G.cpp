#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <cassert>
using namespace std;
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define mp make_pair
#define fi first
#define se second
#define pb push_back
const int N=3100;
struct bian{
    int next,point;
}b[N<<1];
int p[N],len,n,pd[N],w[N],K,aw,size[N];
long long f[N][N][3][2],pre[N][3][2];
void ade(int k1,int k2){
    len++; b[len].next=p[k1]; b[len].point=k2;
    p[k1]=len;
}
void add(int k1,int k2){
    ade(k1,k2); ade(k2,k1);
}
const long long inf=1e15,inf2=1e14;
int father[N];
int findfather(int k1){
    if (father[k1]==k1) return k1;
    return father[k1]=findfather(father[k1]);
}
void update(long long &k1,long long k2){
    k1=max(k1,k2);
}
long long ts=0;
void merge(int k1,int k2){
    memcpy(pre,f[k1],sizeof f[k1]);
    for (int i=0;i<=size[k1]+size[k2];i++)
        for (int j=0;j<3;j++)
            f[k1][i][j][0]=f[k1][i][j][1]=-inf;
    int cur,m,tot,rem;
    for (int i=0;i<=size[k2];i++)
        for (int j=0;j<3;j++)
            if (f[k2][i][j][0]>-inf2)
                for (int a=0;a<=size[k1];a++)
                    for (int b=0;b<3;b++)
                        for (int c=0;c<2;c++)
                            if (pre[a][b][c]>-inf2){
                            //    cout<<k1<<" "<<k2<<" "<<i<<" "<<j<<" "<<a<<" "<<b<<" "<<c<<" "<<dp[k2][i][j]<<" "<<pre[a][b][c]<<endl;
                                cur=(j||b||c);
                                for (m=0;m<=min(j,b);m++){
                                    tot=i+a+m;
                                    rem=j+b-(m<<1);
                            //    cout<<tot<<" "<<rem<<" "<<cur<<" "<<dp[k2][i][j]+pre[a][b][c]-(j-m)*aw<<endl;
                                    if (rem<3) update(f[k1][tot][rem][cur],f[k2][i][j][0]+pre[a][b][c]-(j-m)*aw);
                                }
                            }
    size[k1]+=size[k2];
}
void treedp(int k1,int k2){
    size[k1]=1;
    for (int i=0;i<=size[k1];i++)
        for (int j=0;j<3;j++)
            f[k1][i][j][0]=f[k1][i][j][1]=-inf;
    f[k1][0][0][0]=0;
    if (pd[k1]){
        for (int i=1;i<3;i++) f[k1][0][i][1]=-aw*i;
    }
    for (int i=p[k1];i;i=b[i].next){
        int j=b[i].point;
        if (j!=k2){
            treedp(j,k1);
            merge(k1,j);
        }
    }
    for (int i=0;i<=size[k1];i++){
        for (int j=0;j<3;j++){
            for (int k=0;k<=j;k++){
                if (pd[k1]==0&&j!=k) continue;
                update(f[k1][i+j-k][k][0],f[k1][i][j][1]+w[k1]);
            }
        }
    }
    /*cout<<"asd"<<k1<<endl;
    for (int i=0;i<=size[k1];i++){
        for (int j=0;j<3;j++) cout<<dp[k1][i][j]<<" "; cout<<endl;
    }*/
}
void solve(){
    scanf("%d%d",&n,&aw); len=0; 
    assert(n<=3000);
    for (int i=1;i<=n;i++) p[i]=0,father[i]=i;
    for (int i=1;i<=n;i++) scanf("%d",&pd[i]);
    for (int i=1;i<=n;i++) scanf("%d",&w[i]);
    for (int i=1;i<n;i++){
        int k1,k2; scanf("%d%d",&k1,&k2);  //cerr<<k1<<" "<<k2<<endl;
        assert(1<=k1&&k1<=n&&1<=k2&&k2<=n);
        add(k1,k2);
        if (findfather(k1)==findfather(k2)) assert(0);
        father[findfather(k1)]=findfather(k2);
    }
    treedp(1,0);
    for (int i=1;i<=n;i++) update(f[1][i][0][0],f[1][i-1][0][0]);
    for (int i=1;i<=n;i++){
        printf("%lld",f[1][i][0][0]);
        if (i==n) puts(""); else putchar(' ');
    }
}
int main(){
    int t; scanf("%d",&t);
    for (;t;t--) solve();
    return 0;
}

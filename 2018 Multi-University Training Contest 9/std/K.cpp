#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int mo=998244353;
int quick(int k1,int k2){
    int k3=1;
    while (k2){
        if (k2&1) k3=1ll*k3*k1%mo;
        k2>>=1; k1=1ll*k1*k1%mo;
    }
    return k3;
}
int dp[2][3],A[2][3],f[2][3];
void update(int &k1,long long k2){
    k1=(k1+k2)%mo;
}
void update(){
    memcpy(f,dp,sizeof dp);
    memset(dp,0x00,sizeof dp);
    for (int i=0;i<2;i++)
        for (int j=0;j<3;j++)
            for (int k=0;k<2;k++)
                for (int a=0;a<3;a++){
                    update(dp[min(i+k,1)][min(j+a,2)],1ll*A[i][j]*f[k][a]);
                }
}
void solve(){
    int a,b,c,d; scanf("%d%d%d%d",&a,&b,&c,&d);
    memset(dp,0x00,sizeof dp);
    dp[0][0]=quick(2,a);
    memset(A,0x00,sizeof A);
    A[0][0]=1;
    A[0][1]=b;
    A[0][2]=(quick(2,b)-b-1+mo)%mo;
    update();
    memset(A,0x00,sizeof A);
    A[0][0]=1;
    A[1][0]=(quick(2,c)-1)%mo;
    update();
    memset(A,0x00,sizeof A);
    A[0][0]=1;
    A[1][1]=d;
    A[1][2]=(quick(2,d)-d-1+mo)%mo;
    update();
    int ans=(quick(2,a+b+c+d)-dp[1][2]+mo)%mo;
    printf("%d\n",ans);
}
int main(){
    int t; scanf("%d",&t);
    for (;t;t--) solve();
    return 0;
}

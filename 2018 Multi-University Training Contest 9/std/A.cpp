#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
const int N=82;
int dp[2][N][N],mo;
int n,m;
void update(int &k1,long long k2){
    k1=(k1+k2)%mo;
}
void solve(){
    scanf("%d%d%d",&n,&m,&mo);
    memset(dp,0x00,sizeof dp);
    dp[0][1][1]=n*m; int now=0;
    for (int i=2;i<=n*m;i++){
        int ne=now^1;
        memset(dp[ne],0x00,sizeof dp[ne]);
        for (int j=0;j<=n;j++)
            for (int k=0;k<=m;k++)
                if (dp[now][j][k]){
                    // cout<<i<<" "<<j<<" "<<k<<" "<<dp[now][j][k]<<endl;
                    int k1=dp[now][j][k];
                    int tot=j*k-i+1,ex1;
                    update(dp[ne][j][k],1ll*k1*(j*k-i+1));
                    update(dp[ne][j+1][k],1ll*k1*k*(n-j));
                    update(dp[ne][j][k+1],1ll*k1*j*(m-k));
                }
        now=ne;    
    }
    printf("%d\n",dp[now][n][m]);    
}
int main(){
    int t; scanf("%d",&t);
    for (;t;t--) solve();
    return 0;    
}

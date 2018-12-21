#include<stdio.h>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<cmath>
#include<iostream>
#include<assert.h>
#include<queue>
#include<string>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
const int N=5100,mo=998244353;
int n,m,K,ans,ma;
short pd[N][N],imp[N][N],d[N][N],id[N][N],B[N],s[N];
char ch[N];
struct atom{
    int l,r;
};
vector<atom>A[N];
int L[N][N],f[N][N],R[N][N];
vector<atom> get(short int *A){
    int pre=1; vector<atom> ans;
    for (int i=2;i<=m+1;i++)
        if (i>m||A[i]!=A[i-1]){
            ans.pb((atom){pre,i-1}); pre=i;
        }
    return ans;
}
inline void update(int &k1,int k2){
    k1=(k1+k2)%mo;
}
void insert(int d,int l,int r,int w){
    if (d>n){
        update(ans,w); return;
    }
    int k1=id[d][l-1],k2=id[d][r+1];
    assert(k1<k2);
    update(f[d][k1+1],w);
    update(f[d][k2],mo-w);
    if ((imp[d][l]&1)==0) update(R[d][l],w);
    if ((imp[d][r]&2)==0) update(L[d][r],w);
}
void solve(){
    scanf("%d%d%d",&n,&m,&K);
    for (int i=1;i<=n;i++){
        scanf("%s",ch+1);
        for (int j=1;j<=m;j++) pd[i][j]=ch[j]-'0';
    }
    for (int i=1;i<=n;i++) A[i]=get(pd[i]);
    for (int i=1;i<=n;i++){
        id[i][0]=-1; id[i][m+1]=A[i].size();
        for (int j=0;j<A[i].size();j++){
            int l=A[i][j].l,r=A[i][j].r;
            for (int k=l;k<=r;k++){
                id[i][k]=j,imp[i][k]=(k==l)+(k==r)*2;
            }
        }
    }
    for (int i=1;i<=m;i++) d[n][i]=n+1;
    for (int now=n-1;now;now--){
        memcpy(B,d[now+1],sizeof d[now+1]);
        for (int i=1;i<=m;i++) if (imp[now+1][i]) B[i]=now+1;
        int head=0,no=1,cur=1;
        for (int i=1;i<=m;i++){
            while (cur<=m&&cur<=i+K){
                while (head>=no&&B[s[head]]>=B[cur]) head--;
                s[++head]=cur; cur++;
            }
            while (s[no]<i-K) no++;
            d[now][i]=B[s[no]];
        }
    }
/*    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++) cout<<d[i][j]<<" " ;cout<<endl;
    }*/
    for (int i=0;i<=n+1;i++)
        for (int j=0;j<=m+1;j++) f[i][j]=L[i][j]=R[i][j]=0;
    f[1][0]=1; ans=0;
    for (int now=1;now<=n;now++){
        for (int i=1;i<A[now].size();i++) update(f[now][i],f[now][i-1]);
        for (int i=0;i<A[now].size();i++){
            int l=A[now][i].l,r=A[now][i].r;
            int cur=n+1,del=0;
            for (int j=l;j<r;j++){
                cur=min(cur,(int)d[now][j]); del=(cur-now)*K;
                ma=max(ma,cur-now);
                insert(cur,max(1,l-del),min(m,j+del),L[now][j]);
            //    if (L[now][j]) cout<<"L "<<now<<" "<<j<<" "<<L[now][j]<<endl;
            }
            cur=n+1;
            for (int j=r;j>l;j--){
                cur=min(cur,(int)d[now][j]); del=(cur-now)*K;
                ma=max(ma,cur-now);
                insert(cur,max(1,j-del),min(m,r+del),R[now][j]);
            //    if (R[now][j]) cout<<"R "<<now<<" "<<j<<" "<<R[now][j]<<endl;
            }
            cur=min(cur,(int)d[now][l]); del=(cur-now)*K;
            insert(cur,max(1,l-del),min(m,r+del),f[now][i]);
            //if (f[now][i]) cout<<"f "<<now<<" "<<i<<" "<<f[now][i]<<endl;
        }
    }
    printf("%d\n",ans);
}
int main(){
    int t; scanf("%d",&t);
    for (;t;t--) solve(); //cerr<<ma<<endl;
    return 0;
}

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cassert>
using namespace std;
int n,m,A[10],B[10];
const int inf=2e9;
struct atom{
    int x,y;
    atom(int _x,int _y){
        x=_x; y=_y;
        x=min(x,inf); y=min(y,inf);
        if (x>y) swap(x,y);
    }
};
int compare(atom k1,atom k2){
    if (k1.x<k2.x) return 1; else if (k1.x>k2.x) return -1;
    if (k1.y<k2.y) return 1; else if (k1.y>k2.y) return -1;
    return 0;
}
int check(atom k1,atom k2,atom k3,atom k4){
    int w=compare(k1,k3); if (w) return w;
    return compare(k2,k4);
}
void solve(){
    scanf("%d%d",&n,&m);
    assert(1<=n&&n<=3&&1<=m&&m<=3);
    for (int i=1;i<=3;i++) A[i]=B[i]=inf;
    for (int i=1;i<=n;i++) scanf("%d",&A[i]);
    for (int i=1;i<=m;i++) scanf("%d",&B[i]);
    for (int i=1;i<=n;i++) assert(1<=A[i]&&A[i]<=1000000000);
    for (int i=1;i<=m;i++) assert(1<=B[i]&&B[i]<=1000000000);
    atom k1=atom(A[1]+2,inf),k2=atom(A[2]+1,A[3]);
    atom k3=atom(B[1]+2,inf),k4=atom(B[2]+1,B[3]);
    if (compare(k1,k2)==-1) swap(k1,k2);
    if (compare(k3,k4)==-1) swap(k3,k4);
    printf("%d\n",check(k1,k2,k3,k4));
}
int main(){
    int t; scanf("%d",&t);
    assert(1<=t&&t<=100000);
    for (;t;t--) solve();
    return 0;
}

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
int A[3],B[3];
void solve(){
    for (int i=0;i<3;i++) scanf("%d",&A[i]);
    for (int i=0;i<3;i++) scanf("%d",&B[i]);
    long long ans=0;
    long long n=1ll*A[0]+A[1]+A[2];
    assert(n==1ll*B[0]+B[1]+B[2]);
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            if (j==(i+1)%3) ans+=1ll*A[i]*B[j];
            else if (i!=j) ans-=1ll*A[i]*B[j];
    long long d=abs(__gcd(ans,1ll*n));
    long long k1=ans/d,k2=n/d;
    if (k2==1) printf("%lld\n",k1); else
    printf("%lld/%lld\n",k1,k2);
}
int main(){
    int t; scanf("%d",&t);
    for (;t;t--) solve();
    return 0;
}

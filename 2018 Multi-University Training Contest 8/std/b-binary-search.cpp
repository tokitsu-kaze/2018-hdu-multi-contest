#include<bits/stdc++.h>
#define eps 1e-8

using namespace std;
typedef long long ll;
struct point{
    ll x,y;
    point operator-(const point &u){
        return {x-u.x,y-u.y};
    }
    ll operator^(const point &u){
        return x*u.y-y*u.x;
    }
    void read(){
        scanf("%lld%lld",&x,&y);
    }
}p[3];
ll dis(point u){
    return u.x*u.x+u.y*u.y;
}
long double sqrt_(long double x){
    return sqrt(max((long double)0,x));
}
ll d,S,a[3],b[3],res;
bool flag;
long double w[3],x,ans,l,r,mid;

int main(){
    int N;cin >> N;
    while (N--){
        for (int i=0;i<3;i++) p[i].read(); scanf("%lld",&d);
        S=abs((p[1]-p[0])^(p[2]-p[0])); flag=false;
        for (int i=0;i<3;i++) b[i]=dis(p[(i+1)%3]-p[i]),w[i]=sqrt((long double)b[i]),a[i]=i;
        for (int i=0;i<3;i++) if (S*S<=b[i]*d*d) flag=true;
        if (!flag){
            printf("impossible\n");continue;
        }
        ans=1e9;
        for (int i=0;i<3;i++) if (d>w[i]) ans=min(ans,(long double)S/w[i]);
        do{
            //printf("%.10Lf\n",ans);
            res=b[(a[1]+1)%3]-d*d;
            if (b[(a[1]+1)%3]>=b[(a[0]+1)%3]+b[(a[2]+1)%3]
            && (S*S<=d*d*b[(a[0]+1)%3])&&(S*S<=res*b[(a[2]+1)%3])) {
                ans=min(ans,sqrt((long double)res));
            }
            if (d*d>b[a[0]]) continue;
            x=sqrt((long double)(b[a[0]]-d*d));
            l=x; r=min(w[a[2]],w[a[1]]+x);
            if (l+eps>r) continue;
            //if (b[a[1]]<(r-x)*(r-x)||b[a[2]]<r*r) continue;
            if (sqrt_((long double)b[a[1]]-(r-x)*(r-x))+sqrt_((long double)b[a[2]]-r*r)>(long double)d+eps) continue;
            //printf("%.10Lf\n",sqrt((long double)b[a[1]]-(r-x)*(r-x)+eps*eps/5)+sqrt((long double)b[a[2]]-r*r+eps*eps/5));
            while (r-l>eps){
                mid=(l+r)/2;
                if (sqrt_((long double)b[a[1]]-(mid-x)*(mid-x))+sqrt_((long double)b[a[2]]-mid*mid)>(long double)d+eps) l=mid; else r=mid;
            }
            if (l-r<eps) ans=min(ans,l);
        }while (next_permutation(a,a+3));
        for (int i=0;i<3;i++) ans=max(ans,(long double)1.0*sqrt_((long double)1.0*(b[i]-d*d)));
        printf("%.10Lf\n",ans);
    }
}
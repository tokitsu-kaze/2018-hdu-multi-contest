#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N=110000;
const int mo=998244353;
struct bian{
    int next,point,w;
}b[N<<1];
int p[N],len,n;
void ade(int k1,int k2,int k3){
    len++; b[len].next=p[k1];
    b[len].point=k2; b[len].w=k3; p[k1]=len;
}
void add(int k1,int k2,int k3){
    ade(k1,k2,k3); ade(k2,k1,k3);
}
struct atom{
    int l1,l2,l3,c3;
    void init(){
        l2=l3=c3=0; l1=1;
    }
    void print(){
        cout<<l1<<" "<<l2<<" "<<l3<<" "<<c3<<endl;
    }
}f[N<<1];
void update(int &k1,long long k2){
    k1=(k1+k2)%mo;
    if (k1<0) k1+=mo;
}
atom addroot(atom k1){
    atom res; res.init();
    res.l2=k1.l1; res.l3=k1.l2;
    return res;
}
atom operator + (atom k1,atom k2){
    atom res; res.init();
    update(res.l3,k1.l3+k2.l3);
    update(res.l2,k1.l2+k2.l2);
    update(res.c3,k1.c3+k2.c3+1ll*k1.l2*k2.l2);
    return res;
}
void treedp(int k1,int k2,int loc){
    f[loc].init();
    for (int i=p[k1];i!=-1;i=b[i].next){
        int j=b[i].point;
        if (j!=k2){
            treedp(j,k1,i);
            f[loc]=f[loc]+addroot(f[i]);
        }
    }
}
atom L[N],R[N];
void treedp2(int k1,int k2,int fa){
    int len=0;
    for (int i=p[k1];i!=-1;i=b[i].next){
        int j=b[i].point;
        if (j!=k2){
            len++; L[len]=addroot(f[i]); R[len]=addroot(f[i]);
        }
    }
    L[0].init(); R[len+1].init();
    for (int i=1;i<=len;i++) L[i]=L[i-1]+L[i];
    for (int i=len;i;i--) R[i]=R[i+1]+R[i];
    /*cout<<"asd "<<k1<<endl;
    for (int i=1;i<=len;i++) L[i].print();
    cout<<endl;
    for (int i=1;i<=len;i++) R[i].print();*/
    len=0;
    for (int i=p[k1];i!=-1;i=b[i].next){
        int j=b[i].point;
        if (j!=k2){
            len++; f[i^1]=L[len-1]+R[len+1];
            if (fa!=-1) f[i^1]=f[i^1]+addroot(f[fa]);
            /*cout<<"update "<<(i^1)<<" "<<len<<endl;
            L[len-1].print(); R[len+1].print(); f[i^1].print();
            addroot(f[fa]).print();*/
        }
    }
    for (int i=p[k1];i!=-1;i=b[i].next){
        int j=b[i].point;
        if (j!=k2) treedp2(j,k1,i^1);
    }
}
int num[N<<1],totd[N<<1];
void treedp3(int k1,int k2,int k3){
    num[k3]=(f[k3].l3+f[k3].c3)%mo; totd[k3]=0;
    for (int i=p[k1];i!=-1;i=b[i].next){
        int j=b[i].point;
        if (j!=k2){
            treedp3(j,k1,i);
            update(num[k3],num[i]);
            update(totd[k3],totd[i]+1ll*num[i]*b[i].w);
        }
    }
}
void treedp4(int k1,int k2,int fa){
    int A=0,B=0;
    if (fa!=-1){
        A=num[fa]; B=totd[fa];
        update(B,1ll*A*b[fa].w);
    }
    for (int i=p[k1];i!=-1;i=b[i].next){
        int j=b[i].point;
        if (j!=k2){
            update(A,num[i]);
            update(B,totd[i]+1ll*num[i]*b[i].w);
        }
    }
    for (int i=p[k1];i!=-1;i=b[i].next){
        int j=b[i].point;
        if (j!=k2){
            int loc=i^1;
            num[loc]=A; totd[loc]=B;
            update(num[loc],-num[i]);
            update(totd[loc],-totd[i]-1ll*num[i]*b[i].w);
            update(num[loc],f[i^1].c3+f[i^1].l3);
            treedp4(j,k1,i^1);
        }
    }
}
int ans;
vector<pair<int,int> >C;
int outw[N],outd[N];
void solvec(int k1){
//    cout<<"solvec "<<k1<<endl;
    int tot=0; C.clear();
    for (int i=p[k1];i!=-1;i=b[i].next){
        int j=b[i].point;
        int nu=(1ll*num[i]+outd[j]-1)%mo;
        C.pb(mp(b[i].w,nu));
        update(tot,nu);
    }
    sort(C.begin(),C.end());
    int prew=0,pren=0,prewn=0;
    update(tot,1ll*(outd[k1]-2)*(outd[k1]-3)/2);
    //cout<<tot<<endl;
    for (int i=0;i<C.size();i++){
        int num=0;
        update(num,3ll*prew*tot);
        update(num,1ll*C[i].fi*i%mo*tot);
        update(num,-3ll*prewn);
        update(num,-1ll*C[i].fi*pren);
        update(num,-3ll*prew*C[i].se);
        update(num,-1ll*i*C[i].fi%mo*C[i].se);
        update(prew,C[i].fi);
        update(pren,C[i].se);
        update(prewn,1ll*C[i].fi*C[i].se);
        update(ans,2*num);
    }
    update(tot,-1ll*(outd[k1]-2)*(outd[k1]-3)/2);
    update(tot,1ll*(outd[k1]-1)*(outd[k1]-2)/2);
    for (int i=p[k1];i!=-1;i=b[i].next){
        int j=b[i].point;
        int rem=(1ll*tot-num[i]-(outd[j]-1))%mo;
        int totw=(3ll*b[i].w*(outd[j]-1)+outw[j]-b[i].w)%mo;
        update(ans,2ll*rem*totw);
    }
}
void solveco(int u,int v,int w){
    int sizel=outd[u]-1,sizer=outd[v]-1;
    update(ans,4ll*sizel*sizer%mo*w);
    update(ans,2ll*(outw[u]-w)*sizer);
    update(ans,2ll*(outw[v]-w)*sizel);

    update(ans,2ll*sizel*(sizel-1)%mo*w);
    update(ans,2ll*(outw[u]-w)*(sizel-1));

    update(ans,2ll*sizer*(sizer-1)%mo*w);
    update(ans,2ll*(outw[v]-w)*(sizer-1));
}
int father[N];
int findfather(int k1){
    if (father[k1]==k1) return k1;
    return father[k1]=findfather(father[k1]);
}
void solve(){
    scanf("%d",&n); len=-1;
    for (int i=1;i<=n;i++) p[i]=-1,father[i]=i;
    for (int i=1;i<n;i++){
        int k1,k2,k3; scanf("%d%d%d",&k1,&k2,&k3);
        add(k1,k2,k3);
        assert(1<=min(k1,k2)&&max(k1,k2)<=n);
        assert(findfather(k1)!=findfather(k2));
        father[k1]=findfather(father[k2]);
    }
    treedp(1,0,len+1); //cout<<"finish1"<<endl;
    treedp2(1,0,-1); //cout<<"finish2"<<endl;
    treedp3(1,0,len+1); //cout<<"finish3"<<endl;
    treedp4(1,0,-1); ans=0; //cout<<"finish4"<<endl;
    //for (int i=0;i<=len+1;i++) cout<<b[i].point<<" "<<b[i^1].point<<" "<<f[i].c3<<" "<<f[i].l3<<" "<<num[i]<<" "<<totd[i]<<endl;
    
    for (int i=0;i<=len;i++){
        update(totd[i],1ll*num[i]*b[i].w);
        update(ans,4ll*totd[i]*(f[i^1].c3+f[i^1].l3));
    }
    //cout<<ans<<endl;
    for (int now=1;now<=n;now++){
        outw[now]=0; outd[now]=0;
        for (int i=p[now];i!=-1;i=b[i].next) update(outw[now],b[i].w),outd[now]++;
    }
    //cout<<"finish5"<<endl;
    for (int r=1;r<=n;r++) solvec(r);
    for (int i=0;i<=len;i+=2){
        solveco(b[i].point,b[i^1].point,b[i].w);
        //cout<<b[i].point<<" "<<b[i^1].point<<" "<<b[i].w<<" "<<ans<<endl;
    }
    ans=1ll*ans*(mo+1)/2%mo;
    printf("%d\n",ans);
}
int main(){
    int t; scanf("%d",&t);
    for (;t;t--) solve();
    return 0;
}

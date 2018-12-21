#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;
#define mp make_pair
#define fi first
#define se second
const int N=1010000,S=300;
int n,m,A[N],where[N],len,R[N],w[N],a[N],glb,tag[N];
int compare(int k1,int k2){
    return A[k1]<A[k2];
}
struct atom{
    int t,w,tag;
};
struct block{
    int l,r,id,lenL,lenR;
    pair<int,int>* L;
    pair<int,int>* R;
    queue<atom>Q;
    int now,cl;
    long long sum;
    void init(int _l,int _r,int _id){
        if (L!=nullptr) delete[] L;
        if (R!=nullptr) delete[] R;
        L = new pair<int,int>[_r - _l + (S << 1)];
        R = new pair<int,int>[_r - _l + (S << 1)];
        l=_l; r=_r; sum=0; id=_id;
        for (int i=l;i<=r;i++) R[i-l]=mp(A[i],tag[A[i]]),sum+=w[A[i]];
        L[0]=mp(A[l],tag[A[l]]);
        lenL=1; lenR=r-l+1;
        //cout<<"init "<<id<<" "<<l<<" "<<r<<" "<<sum<<endl;
        while (!Q.empty()) Q.pop();
        for (int i=l+1;i<=r;i++) Q.push((atom){i-l,A[i],tag[A[i]]});
        cl=r-l; now=0;
        make_heap(R,R+lenR);
    }
    int getl(){
        while (1){
            int k1=L[0].fi;
            if (L[0].se!=tag[k1]){
                pop_heap(L,L+lenL,greater<pair<int,int> >()); lenL--; continue;
            }
            return k1;
        }
    }
    int getma(){
        while (1){
            int k1=R[0].fi;
            if (R[0].se!=tag[k1]){
                pop_heap(R,R+lenR); lenR--; continue;
            }
            return k1;
        }
    }
    void pushL(pair<int,int> k1){
        L[lenL]=k1; lenL++;
        push_heap(L,L+lenL,greater<pair<int,int> >());
    }
    void pushR(pair<int,int> k1){
        R[lenR]=k1; lenR++;
        push_heap(R,R+lenR);
    }
    void addclock(){
        now++; cl++;
        while (!Q.empty()){
            atom k1=Q.front();
            if (k1.t<=now){
                if (k1.tag==tag[k1.w]){
                    pushL(mp(k1.w,k1.tag));
                }
                Q.pop();
            } else break;
        }
    }
    void writeback(){
        for (int i=l;i<=r;i++){
            A[i]=getl(); 
            pop_heap(L,L+lenL,greater<pair<int,int> >()); lenL--;
            addclock();
        }
    }
    void changel(int k1,int tag){
        pushL(mp(k1,tag)); pushR(mp(k1,tag));
    }
    void changer(int k1,int tag){
        //if (id==29) cout<<"changer "<<k1<<endl;
        if (now>=cl) pushL(mp(k1,tag)); else Q.push((atom){cl,k1,tag});
        pushR(mp(k1,tag));
    }
}B[S*3];
void rebuild(int k1){
    B[k1].init(R[k1-1]+1,R[k1],k1);
}
long long query(int l,int r){
    long long ans=0;
    for (int i=where[l];i<=where[r];i++) ans+=B[i].sum;
    return ans;
}
void change(int l,int r){
    int pre=-100;
    for (int i=where[l];i<=where[r];i++){
        int now=B[i].getl();
        if (pre>now){
            glb++; tag[now]=tag[pre]=glb;
            B[i-1].changer(now,glb);
            B[i].changel(pre,glb);
            B[i].sum+=w[pre]-w[now];
            B[i-1].sum+=w[now]-w[pre];
        }
        B[i].addclock();
        pre=B[i].getma();
    }
}
struct query{
    int type,l,r;
    void scan(){
        scanf("%d%d%d",&type,&l,&r);
    }
}q[40000];
void solve(int l,int r){
    //cerr<<l<<" "<<r<<endl;
    len=0;
    for (int i=l;i<=r;i++){
        if (q[i].l>1) R[++len]=q[i].l-1;
        R[++len]=q[i].r;
    }
    sort(R+1,R+len+1);
    len=unique(R+1,R+len+1)-R-1;
    for (int i=1;i<=len;i++)
        for (int j=R[i-1]+1;j<=R[i];j++) where[j]=i;
    //for (int i=1;i<=len;i++) cout<<R[i]<<" "; cout<<endl;
    //for (int i=1;i<=n;i++) cout<<where[i]<<" "; cout<<endl;
    where[n+1]=len+1;
    for (int i=1;i<=len;i++) rebuild(i);
    for (int i=l;i<=r;i++)
        if (q[i].type==1) change(q[i].l,q[i].r);
        else printf("%lld\n",query(q[i].l,q[i].r));
    for (int i=1;i<=len;i++) B[i].writeback();
}
void solve(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d",&A[i]);
    for (int i=1;i<=n;i++) a[i]=i;
    sort(a+1,a+n+1,compare);
    for (int i=1;i<=n;i++) w[i]=A[a[i]],A[a[i]]=i;
    for (int i=1;i<=m;i++) q[i].scan();
    for (int i=1,r=min(S,m);i<=m;i=r+1,r=min(r+S,m))
        solve(i,r);
}
int main(){
    int t=1; //scanf("%d",&t);
    for (;t;t--) solve();
    return 0;
}

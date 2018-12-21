#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+100;
const int N = 1e4+100;
const int MOD = 1e9+7;
string s[N];
int a[N];
int n,m;
int bas[maxn];
int Ans[maxn];
struct Suffix_Automaton{
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    int ans[maxn*2];
    int flag[maxn*2];
    bool built[maxn*2];
    void clear(){
        last =cnt=1;
        fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(string s){
        for (int i=0;i<s.size();i++){
            add(s[i]-'a');
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        l[np] = l[p]+1;
        ans[np] =1;
        last = np;
        while (p&&!nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np]=1;
        else{
            int q = nxt[p][c];
            if (l[q]==l[p]+1)fa[np] =q;
            else{
                int nq = ++ cnt;
                ans[nq]=1;
                l[nq] = l[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof (nxt[q]));
                fa[nq] =fa[q];
                fa[np] = fa[q] =nq;
                while (nxt[p][c]==q)nxt[p][c] =nq,p = fa[p];
            }
        }
    }
    void build(string s,int V,int tag){
        int now =1;
        for (int i=0;i<s.size();i++){
            now = nxt[now][s[i]-'a'];
            int temp = now;
            while (temp!=1&&flag[temp]!=tag){
                ans[temp] = 1LL*ans[temp]*V%MOD;
                flag[temp] =tag;
                temp = fa[temp];
            }
        }
    }
    void build(int now){
        built[now]=1;
        Ans[l[fa[now]]+1] = (Ans[l[fa[now]]+1]+ans[now])%MOD;
        Ans[l[now]+1] = (Ans[l[now]+1]-ans[now]+MOD)%MOD;
        for (int i=0;i<26;i++){
            if(!nxt[now][i]||built[nxt[now][i]])continue;
            build(nxt[now][i]);
        }
    }
}sam;
int power(int x,int y){
  int ret =1;
  while (y){
    if(y&1){
      ret = 1LL*ret*x%MOD;
    }
    y>>=1;
    x = 1LL*x*x%MOD;
  }
  return ret;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    sam.clear();
    for (int i=0;i<n;i++){
        cin>>s[i];
        sam.init(s[i]);
        sam.last=1;
    }
    for (int i=0;i<n;i++){
        cin>>a[i];
    }
    for (int i=0;i<n;i++){
        sam.build(s[i],a[i],i+1);
    }
    sam.ans[1]=0;
    sam.build(1);
    for (int i=1;i<maxn;i++){
      Ans[i] = (Ans[i-1]+Ans[i])%MOD;
    }
    for (int i=1;i<maxn;i++){
      Ans[i] = (Ans[i]+Ans[i-1])%MOD;
    }
    bas[0]=1;
    for (int i=1;i<maxn;i++){
      bas[i] = 26LL*bas[i-1]%MOD;
    }
    for (int i=2;i<maxn;i++){
      bas[i] = (bas[i]+bas[i-1])%MOD;
    }
    for (int i=1;i<maxn;i++){
      Ans[i] = 1LL*Ans[i]*power(bas[i],MOD-2)%MOD;
    }
    cin>>m;
    while (m--){
      int x;
      cin>>x;
      cout<<Ans[x]<<'\n';
    }
    return 0;
}

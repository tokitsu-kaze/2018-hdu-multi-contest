//Copyright(c)2018 Mstdream
#include<bits/stdc++.h>
using namespace std;

inline void splay(int &v){
	v=0;char c=0;int p=1;
	while(c<'0' || c>'9'){if(c=='-')p=-1;c=getchar();}
	while(c>='0' && c<='9'){v=(v<<3)+(v<<1)+c-'0';c=getchar();}
	v*=p;
}
const int N=100010;
int f[N][20],fir[N],nxt[N],sz,fa[N],to[N];
void add(int x,int y){
	nxt[++sz]=fir[x],fir[x]=sz,to[sz]=y;
}
void dfs(int x){
	f[x][0]=fa[x];
	for(int i=1;i<=19;i++)f[x][i]=f[f[x][i-1]][i-1];
	for(int u=fir[x];u;u=nxt[u])dfs(to[u]);
}
int jmp(int x,int num){
	for(int i=19;i>=0;i--){
		if(num>=(1<<i)){
			num-=(1<<i);
			x=f[x][i];
		}
	}
	return x;
}
vector<int>v[N];
int a[N],b[N],t[N],cnt[N],tot,bel[N],P,q[N],n,m,vis[N],idx;
#define re(x) memset(x,0,sizeof x)
void init(){
	re(a),re(b),re(t),re(cnt),tot=0,re(bel),P=0,re(q),n=0,m=0,re(vis),idx=0;
	re(f),re(fir),re(nxt),sz=0,re(fa),re(to);
	for(int i=0;i<N;i++)v[i].clear();
}
void bfs(){
	++tot;v[tot].push_back(0);
	bel[0]=1;
	int l=0,r=1;q[1]=1;
	while(l!=r){
		l++;
		if(fa[q[l]]!=0&&v[bel[fa[q[l]]]].size()<P){
			bel[q[l]]=bel[fa[q[l]]];
			v[bel[q[l]]].push_back(q[l]);
		}
		else{
			++tot;v[tot].push_back(q[l]);
			bel[q[l]]=tot;
		}
		int x=jmp(q[l],a[q[l]]);
		if(bel[q[l]]==bel[x]){
			cnt[q[l]]=cnt[x]+1;
			b[q[l]]=b[x];
		}
		else{
			cnt[q[l]]=1;
			b[q[l]]=x;
		}
		t[q[l]]=x;
		for(int u=fir[q[l]];u;u=nxt[u]){
			q[++r]=to[u];
		}
	}
}
void Main(){
	splay(n);P=sqrt(n)+1;
	for(int i=2;i<=n;i++)splay(fa[i]),add(fa[i],i);
	for(int i=1;i<=n;i++)splay(a[i]);
	dfs(1);bfs();
	splay(m);
	for(int op,x,y;m--;){
		splay(op);
		if(op==1){
			int ans=0;
			splay(x);
			while(x){
				ans+=cnt[x];
				x=b[x];
			}
			printf("%d\n",ans);
		}
		else{
			splay(x),splay(y);
			a[x]=y;t[x]=jmp(x,y);
			if(bel[x]!=bel[t[x]]){
				cnt[x]=1;
				b[x]=t[x];
			}
			else{
				cnt[x]=cnt[t[x]]+1;
				b[x]=b[t[x]];
			}
			++idx;vis[x]=idx;
			for(int i=0;i<v[bel[x]].size();i++){
				int now=v[bel[x]][i];
				if(vis[t[now]]==idx){
					cnt[now]=cnt[t[now]]+1;
					b[now]=b[t[now]];
					vis[now]=idx;
				}
			}
		}
	}
}
int main(){
	//freopen("xxx.in","r",stdin);
	//freopen("xxx.out","w",stdout);
	int T;cin>>T;
	for(;T--;){
		//cerr<<T<<endl;
		init();
		Main();
	}
}

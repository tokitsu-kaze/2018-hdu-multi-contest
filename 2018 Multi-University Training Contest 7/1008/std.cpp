//#pragma comment(linker,"/STACK:102400000000,102400000000")
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
int T,n,m;
ll D[2][100005];
void Update(int o,int p,ll v){
	for(;p<=n;p+=(p&(-p))){
		D[o][p]+=v;
	}
}
ll Query(int o,int p){
	ll res=0;
	for(;p;p-=(p&(-p))){
		res+=D[o][p];
	}
	return res;
}
void Update(int o,int L,int R,ll v){
	Update(o,L,v);
	if(R!=n){
		Update(o,R+1,-v);
	}
}
struct Edge{
	int v,w,id;
	Edge(const int &v,const int &w,const int &id){
		this->v=v;
		this->w=w;
		this->id=id;
	}
	Edge(){}
};
vector<Edge>G[100005];
typedef vector<Edge>::iterator ITER;
int Fa[100005],dep[100005],top[100005],son[100005],siz[100005];
void dfs(int U){
	siz[U]=1;
	for(ITER it=G[U].begin();it!=G[U].end();++it){
		if((it->v)!=Fa[U]){
			Fa[it->v]=U;
			dep[it->v]=dep[U]+1;
			dfs(it->v);
			siz[U]+siz[it->v];
			if(siz[it->v]>siz[son[U]]){
				son[U]=(it->v);
			}
		}
	}
}
void dff(int U){
	if(son[U]){
		top[son[U]]=top[U];
		dff(son[U]);
	}
	for(ITER it=G[U].begin();it!=G[U].end();++it){
		if((it->v)!=Fa[U] && (it->v)!=son[U]){
			top[it->v]=(it->v);
			dff(it->v);
		}
	}
}
int lca(int U,int V){
	while(top[U]!=top[V]){
		if(dep[top[U]]<dep[top[V]]){
			swap(U,V);
		}
		U=Fa[top[U]];
	}
	if(dep[U]>dep[V]){
		swap(U,V);
	}
	return U;
}
int fa[100005];
int findroot(int x){
	return fa[x]==x ? x : fa[x]=findroot(fa[x]);
}
int e,v[200005],first[100005],nex[200005],w[200005],id[200005];
void AddEdge(int U,int V,int W,int ID){
	v[++e]=V;
	w[e]=W;
	id[e]=ID;
	nex[e]=first[U];
	first[U]=e;
}
bool vis[100005];
int path[100005],pat;
bool onhuan[100005],bianonhuan[100005];
int x,y,op,z;
bool df1(int U,int d){
	vis[U]=1;
	path[d]=U;
	if(U==y){
		pat=d;
		for(int i=1;i<=d;++i){
			onhuan[path[i]]=1;
		}
		return 1;
	}
	for(int i=first[U];i;i=nex[i])if(!vis[v[i]]){
		if(df1(v[i],d+1)){
			return 1;
		}
	}
	return 0;
}
int bel[100005];
int Ls[100005],Rs[100005],tot;
int huanid[100005],xifu[100005];
void df2(int U,int rt,ll d){
	vis[U]=1;
	bel[U]=rt;
	Ls[U]=++tot;
	if(U!=rt){
		Update(1,Ls[U],Ls[U],d);
	}
	for(int i=first[U];i;i=nex[i]){
		if(!vis[v[i]] && !onhuan[v[i]]){
			xifu[id[i]]=v[i];
			df2(v[i],rt,d+(ll)w[i]);
		}
	}
	Rs[U]=tot;
}
ll sum;
void dfhuan(int U,int d){
	vis[U]=1;
	huanid[U]=d;
	for(int i=first[U];i;i=nex[i]){
		if(!vis[v[i]] && onhuan[v[i]]){
			Update(0,d,(ll)w[i]);
			xifu[id[i]]=U;
			bianonhuan[id[i]]=1;
			dfhuan(v[i],d+1);
		}
		else if(onhuan[v[i]] && huanid[U]==pat && huanid[v[i]]==1){
			sum=(ll)w[i];
			bianonhuan[id[i]]=1;
		}
	}
}
int root,val[100005];
int main(){
//	freopen("k.in","r",stdin);
//	freopen("k.out","w",stdout);
	scanf("%d",&T);
	for(;T;--T){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i){
			fa[i]=i;
		}
		for(int i=1;i<=n;++i){
			scanf("%d%d%d",&x,&y,&z);
			val[i]=z;
			int f1=findroot(x),f2=findroot(y);
			if(f1!=f2){
				G[x].push_back(Edge(y,z,i));
				G[y].push_back(Edge(x,z,i));
				fa[f1]=f2;
			}
			else{
				root=x;
				df1(x,1);
			}
			AddEdge(x,y,z,i);
			AddEdge(y,x,z,i);
		}
		top[root]=root;
		dfs(root);
		dff(root);
		memset(vis,0,sizeof(bool)*(n+1));
		for(int i=1;i<=pat;++i){
			df2(path[i],path[i],0);
		}
		memset(vis,0,sizeof(bool)*(n+1));
		dfhuan(path[1],1);
		sum+=Query(0,pat);
		for(int i=1;i<=m;++i){
			scanf("%d%d%d",&op,&x,&y);
			if(op==0){
				if(bianonhuan[x]){
					if(xifu[x]){
						Update(0,huanid[xifu[x]],(ll)(y-val[x]));
					}
					sum+=(ll)(y-val[x]);
				}
				else{
					Update(1,Ls[xifu[x]],Rs[xifu[x]],(ll)(y-val[x]));
				}
				val[x]=y;
			}
			else{
				if(bel[x]!=bel[y]){
					int id1=min(huanid[bel[x]],huanid[bel[y]]);
					int id2=max(huanid[bel[x]],huanid[bel[y]]);
					ll tmp=Query(0,id2-1)-Query(0,id1-1);
					printf("%lld\n",Query(1,Ls[x])+Query(1,Ls[y])+min(tmp,sum-tmp));
				}
				else{
					printf("%lld\n",Query(1,Ls[x])+Query(1,Ls[y])-Query(1,Ls[lca(x,y)])*2ll);
				}
			}
		}
		e=tot=0;
		memset(first,0,sizeof(int)*(n+1));
		memset(val,0,sizeof(int)*(n+2));
		memset(xifu,0,sizeof(int)*(n+2));
		memset(bel,0,sizeof(int)*(n+1));
		memset(vis,0,sizeof(bool)*(n+1));
		memset(huanid,0,sizeof(int)*(n+1));
		memset(Fa,0,sizeof(int)*(n+1));
		memset(dep,0,sizeof(int)*(n+1));
		memset(top,0,sizeof(int)*(n+1));
		memset(son,0,sizeof(int)*(n+1));
		memset(siz,0,sizeof(int)*(n+1));
		memset(D[0],0,sizeof(ll)*(n+1));
		memset(D[1],0,sizeof(ll)*(n+1));
		memset(onhuan,0,sizeof(bool)*(n+1));
		memset(bianonhuan,0,sizeof(bool)*(n+2));
		for(int i=1;i<=n;++i){
			G[i].clear();
		}
	}
	return 0;
}

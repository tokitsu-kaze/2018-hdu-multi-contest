#include<bits/stdc++.h>
using namespace std;

int CASES;
int n,T;

struct R{
	int to,val,nex;
}r[222222];
int hea[111111]={0},cnt=1,fa[111111],dep[111111];
int f1[111111],f2[111111],sch[111111],sz2[111111];

int GF1(int x){
	return x==f1[x]? x: f1[x]=GF1(f1[x]);
}
int GF2(int x){
	return x==f2[x]? x: f2[x]=GF2(f2[x]);
}
void uni1(int y,int x){
	x=GF1(x);y=GF1(y);
	f1[y]=x;
	sch[x]+=sch[y];
}
void uni2(int y,int x){
	x=GF2(x);y=GF2(y);
	f2[y]=x;
	sz2[x]+=sz2[y];
	sch[GF1(fa[y])]-=sz2[y];
	if (fa[x]) sch[GF1(fa[x])]+=sz2[y];
}

void dfs(int x,int fff){
	fa[x]=fff;dep[x]=dep[fff]+1;
	for (int y,i=hea[x];i;i=r[i].nex){
		y=r[i].to;if (y==fff) continue;
		sch[x]++;
		dfs(y,x);
	}
	for (int y,i=hea[x];i;i=r[i].nex){
		y=r[i].to;if (y==fff) continue;
		if (r[i].val==1){
			uni2(y,x);uni1(y,x);
		}else if (r[i].val==2){
			uni2(y,x);
		}
	}
}

void doit(int x,int y){
	if (GF1(x)==GF1(y)) return;
	for (int z;(x=GF1(x))!=(y=GF1(y));x=z){
		if (dep[x]<dep[y]) swap(x,y);
		z=GF1(fa[x]);
		if (GF2(x)==GF2(z)){
			uni1(x,z);
		}else{
			uni2(x,z);
		}
	}
}

void __main(){
	scanf("%d%d",&n,&T);
	int u,v,w;
	for (int i=1;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);w=max(1,w);
		r[++cnt]=(R){v,w,hea[u]};hea[u]=cnt;
		r[++cnt]=(R){u,w,hea[v]};hea[v]=cnt;
	}
	for (int i=1;i<=n;i++){
		f1[i]=f2[i]=i;
		sch[i]=0;sz2[i]=1;
	}
	dep[0]=0;
	dfs(1,0);
	int times=1;
	for (int st,en,fl,ans;T--;times++){
		scanf("%d%d%d%d",&u,&v,&en,&st);
		doit(u,v);
		fl=0;
		if (GF2(st)==GF2(en)) fl=1;
		if (GF1(fa[GF2(st)])==GF1(en)) fl=1;
		if (GF2(fa[GF1(en)])==GF2(st)) fl=1;
		sz2[0]=0;
		ans=sz2[GF2(en)]+sch[GF1(en)]\
			+( GF2(fa[GF1(en)])==GF2(en)? 0: sz2[GF2(fa[GF1(en)])] );
		printf("%d %d\n",fl,ans);
	}

    cnt = 1;
    for (int i = 1; i <= n; ++ i)
        hea[i] = 0;
    for (int i = 1; i <= n; ++ i)
        f1[i] = f2[i] = sch[i] = sz2[i] = fa[i] = dep[i] = 0;
}

int main()
{
    scanf("%d", &CASES);
    while (CASES --)
        __main();
}

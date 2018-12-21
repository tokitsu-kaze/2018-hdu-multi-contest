#include<bits/stdc++.h>
using namespace std;

const int INF=1e8;
const int maxn=2000;
const int maxm=10000;
int n,m,K,W,totnd,SS,TT,id[maxn][2],Ans;
int tote,FIR[maxn],TO[maxm],NEXT[maxm];
int CAP[maxm],COST[maxm];
int dis[maxn],from[maxn],q[400000];
bool vis[maxn];

void addedge(int u,int v,int flow,int cost)
{
	TO[++tote]=v;
	CAP[tote]=flow;
	COST[tote]=cost;
	NEXT[tote]=FIR[u];
	FIR[u]=tote;

	TO[++tote]=u;
	CAP[tote]=0;
	COST[tote]=-cost;
	NEXT[tote]=FIR[v];
	if (v!=TT) FIR[v]=tote;
}

bool findpath()
{
	memset(dis,-0x3f3f3f3f,sizeof(dis));
	memset(from,0,sizeof(from));
	memset(vis,0,sizeof(vis));
	dis[SS]=0;
	int H=0,T=1;
	q[1]=SS; vis[SS]=1;
	while (H-T)
	{
		int u=q[++H];
		for (int p=FIR[u];p;p=NEXT[p]) if (CAP[p])
		{
			int v=TO[p],w=COST[p];
			if (dis[v]<dis[u]+w)
			{
				dis[v]=dis[u]+w;
				from[v]=p;
				if (!vis[v])
				{
					q[++T]=v;
					vis[v]=1;
					if (dis[q[T]]>dis[q[H+1]])
						swap(q[T],q[H+1]);
				}
			}
		}
		vis[u]=0;
	}
	return from[TT];
}

void change()
{
	Ans+=dis[TT];
	for (int v=TT;v!=SS;v=TO[from[v]^1])
	{
		CAP[from[v]]--;
		CAP[from[v]^1]++;
	}
}

int main()
{
	int T,i,u,v,w,op;
	scanf("%d",&T);
	while (T--)
	{
		tote=1;
		memset(FIR,0,sizeof(FIR));

		scanf("%d%d%d%d",&n,&m,&K,&W);
		totnd=0;
		SS=++totnd;
		TT=++totnd;
		id[0][0]=id[0][1]=++totnd;
		for (i=1;i<=n;i++)
			id[i][0]=++totnd,id[i][1]=++totnd;
		id[n+1][0]=id[n+1][1]=TT;
		addedge(SS,id[0][0],K,0);
		for (i=0;i<=n;i++)
		{
			addedge(id[i][0],id[i+1][0],INF,0);
			addedge(id[i][1],id[i+1][1],INF,0);
		}

		for (i=1;i<=m;i++)
		{
			scanf("%d%d%d%d",&u,&v,&w,&op);
			int tmp=++totnd;
			addedge(id[u][op],tmp,1,0);
			addedge(tmp,id[v][!op],1,w);
			addedge(tmp,id[v][op],1,w-W);
		}
		Ans=0;
		while (findpath()) change();
		printf("%d\n",Ans);
	}
}


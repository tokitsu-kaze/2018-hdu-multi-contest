#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

int n,m;
int a[205][205];
int fa[40005];
int List[40005],tot;
bool used[40005];

struct Tree
{
    int l,r;
    int d[2][205];
    int sign[2][205];
    int numb;
    int numw;
}tree[1000];

int Js(int i,int j)
{
    return (i-1)*n+j;
}

inline void splay(int &v){
	v=0;char c=0;int p=1;
	while(c<'0' || c>'9'){if(c=='-')p=-1;c=getchar();}
	while(c>='0' && c<='9'){v=(v<<3)+(v<<1)+c-'0';c=getchar();}
	v*=p;
}

int Find(int k)
{
    if (fa[k]==k) return k;
    else
        {
        if (used[k]==0)
            {
            used[k]=1;
            tot++;
            List[tot]=k;
            }
        return fa[k]=Find(fa[k]);
        }
}

void pushup(int i)
{
    int numb=tree[i*2].numb+tree[i*2+1].numb;
    int numw=tree[i*2].numw+tree[i*2+1].numw;

    for (int j=1;j<=n;j++)
        if (tree[i*2].d[1][j]==tree[i*2+1].d[0][j])
            {
            int a,b;
            a=Find(tree[i*2].sign[1][j]);
            b=Find(tree[i*2+1].sign[0][j]);
            if (a==b) continue;
            fa[a]=b;
            if (used[a]==0)
                {
                used[a]=1;
                tot++;
                List[tot]=a;
                }
            if (tree[i*2].d[1][j]==0) numw--;
            else numb--;
            }
    tree[i].numw=numw;
    tree[i].numb=numb;
    for (int j=1;j<=n;j++)
        {
        tree[i].d[0][j]=tree[i*2].d[0][j];
        tree[i].d[1][j]=tree[i*2+1].d[1][j];

        tree[i].sign[0][j]=Find(tree[i*2].sign[0][j]);
        tree[i].sign[1][j]=Find(tree[i*2+1].sign[1][j]);
        }
}

void Init(int i,int l)
{
    tree[i].numw=tree[i].numb=0;
    for (int j=1;j<=n;j++)
        tree[i].d[0][j]=tree[i].d[1][j]=a[j][l];
    for (int j=1;j<=n;j++)
        tree[i].sign[0][j]=tree[i].sign[1][j]=Js(j,l);
    for (int j=1;j<=n;j++)
        if (a[j][l]!=a[j-1][l] || j==1)
            {
            tree[i].sign[0][j]=tree[i].sign[1][j]=Js(j,l);
            if (a[j][l]==0) tree[i].numw++;
            else tree[i].numb++;
            }
        else tree[i].sign[0][j]=tree[i].sign[1][j]=tree[i].sign[0][j-1];
}

void build(int i,int l,int r)
{
    tree[i].l=l;
    tree[i].r=r;
    if (l==r)
        {
        Init(i,l);
        return ;
        }
    int mid=(tree[i].l+tree[i].r)/2;
    build(i*2,l,mid);
    build(i*2+1,mid+1,r);
    pushup(i);
}

void Change(int i,int y)
{
    if (tree[i].l==tree[i].r && tree[i].l==y)
        {
        Init(i,y);
        return ;
        }
    int mid=(tree[i].l+tree[i].r)/2;
    if (y<=mid) Change(i*2,y);
    else Change(i*2+1,y);
    pushup(i);
}

int main()
{

    int t;
    scanf ("%d",&t);
    while (t--)
        {
        memset(tree,0,sizeof(tree));
        memset(List,0,sizeof(List));
        splay(n);
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
                splay(a[i][j]);
        for (int i=1;i<=n*n;i++)
            fa[i]=i;
        build(1,1,n);
        for (int i=1;i<=n*n;i++)
            fa[i]=i;
        scanf ("%d",&m);
        tot=0;

        memset(used,0,sizeof(used));
        while (m--)
            {
            int x,y,o;
            scanf ("%d",&o);
            if (o==1)
                {
                scanf ("%d",&y);
                for (int i=1;i<=n;i++)
                    a[i][y]=1-a[i][y];
                }
            else
                {
                scanf ("%d %d",&x,&y);
                a[x][y]=1-a[x][y];
                }
            Change(1,y);

            for (int i=1;i<=tot;i++)
                fa[List[i]]=List[i];
            for (int i=1;i<=tot;i++)
                used[List[i]]=0;
            tot=0;

            int numb=tree[1].numb;
            int numw=tree[1].numw;

            for (int j=1;j<=n;j++)
                if (tree[1].d[1][j]==tree[1].d[0][j])
                    {
                    int a,b;
                    a=Find(tree[1].sign[1][j]);
                    b=Find(tree[1].sign[0][j]);
                    if (a==b) continue;
                    fa[a]=b;
                    if (used[a]==0)
                        {
                        used[a]=1;
                        tot++;
                        List[tot]=a;
                        }
                    if (tree[1].d[1][j]==0) numw--;
                    else numb--;
                    }

            printf ("%d %d\n",numw,numb);
            for (int i=1;i<=tot;i++)
                fa[List[i]]=List[i];
            for (int i=1;i<=tot;i++)
                used[List[i]]=0;
            tot=0;
            }
        }
}

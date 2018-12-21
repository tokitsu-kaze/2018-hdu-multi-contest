#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
double p[100],np[100],npp[100],tans[100],M,A,B;
int n,q,L[100];
long long CC[20][20];
long long C(int n,int r)
{
    if(CC[n][r]) return CC[n][r];
    long long nowans=1;
    for(int i=n-r+1;i<=n;++i) nowans*=(long long)i;
    for(int i=1;i<=r;++i) nowans/=i;
    return CC[n][r]=nowans;
}
int main()
{
    scanf("%d%d%lf%lf%lf",&n,&q,&M,&A,&B);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&L[i]);
    }
    sort(L+1,L+n+1);
    npp[0]=1;
    tans[0]=0;
    for(int i=1;i<=n;++i)
    {
        p[i]=(double)L[i]/M;
        np[i]=1-p[i];
        npp[i]=npp[i-1]*np[i];

        int re=n-i;
        double temp=0;
        for(int j=0;j<=re;++j)
        {
            double pp=1;
            for(int k=1;k<=j;++k) pp*=p[i];
            for(int k=j+1;k<=re;++k) pp*=np[i];
            temp+=(double)C(re,j)*pp*(((double)L[i]/((double)j+2.0))+(double)A);
        }
        tans[i]=tans[i-1]+temp*p[i]*npp[i-1];
    }
    int x;
    for(int ii=1;ii<=q;++ii)
    {
        scanf("%d",&x);
        int s=1;
        while(L[s+1]<=x&&s<n) s++;
        double ans=0;
        ans+=tans[s];
        int re=n-s;
        double px=(double)x/M;
        double npx=1;
        for(int i=1;i<=re;++i)
            npx*=(1.0-px);
        ans+=npx*npp[s]*((double)x+B);
        double temp=0;
        for(int i=1;i<=re;++i)
        {
            double pp=1;
            for(int j=1;j<=i;++j) pp*=px;
            for(int j=i+1;j<=re;++j) pp*=(1.0-px);
            temp+=(double)C(re,i)*pp*(((double)x/((double)i+1.0)+(double)A));
        }
        ans+=temp*npp[s];
        printf("%.6lf\n",ans);
    }
}

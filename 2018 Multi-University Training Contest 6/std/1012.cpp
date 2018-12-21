#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<string>
#include<set>
using namespace std;
typedef long long lld;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define mp make_pair
#define eps 1e-8
#define G 9.8
int Sig(double a)
{
    if(a < -eps)
        return -1;
    return a > eps;
}
struct Point
{
    double x,y;
    Point(){}
    Point(double x0,double y0)
    {
        x=x0;
        y=y0;
    }
    Point operator +(Point pt)
    {
        return Point(x+pt.x,y+pt.y);
    }
    Point operator -(Point pt)
    {
        return Point(x-pt.x,y-pt.y);
    }
    double operator *(Point pt)
    {
        return x*pt.y-y*pt.x;
    }
};
Point inter(Point up,Point uq,Point vp,Point vq)
{
    Point ret=up;
    double a=(up-vp)*(vp-vq);
    double b=(up-uq)*(vp-vq);
    double t=a/b;
    ret.x+=(uq.x-up.x)*t;
    ret.y+=(uq.y-up.y)*t;
    return ret;
}
double a,b,x0;
double solve(Point now,Point v,Point &to,Point &nv)
{
    double A=-0.5*a*G;
    double B=v.y*a-v.x*b;
    double C=now.y*a-now.x*b;
    double t=-B-sqrt(B*B-4.0*A*C);
    t/=2.0*A;
    to=Point(v.x*t+now.x,v.y*t-0.5*G*t*t+now.y);
    nv=Point(v.x,v.y-G*t);//change nv
    Point up=to-nv;
    Point uq=up+Point(a,b);
    Point vp=to;
    Point vq=to+Point(-b,a);
    Point o=inter(up,uq,vp,vq);
    nv=o+o-up-to;
    return t;
}
int main()
{
    int cas;
    scanf("%d",&cas);
    for(int cc=1;cc<=cas;cc++)
    {
        double x,y;
        cin >> a >> b >> x >> y;
        x=-x;
        Point now=Point(x,y);
        Point v=Point(0,0);
        int tmp=0;
//        double ans=0;
        while(1)
        {
            Point to,nv;
            double add=solve(now,v,to,nv);
            if(Sig(to.x) <= 0)
            {
//                ans+=-(now.x-x0)/v.x;
                break;
            }
//            ans+=add;
            tmp++;
            now=to;
            v=nv;
        }
        printf("%d\n",tmp);
    }
    return 0;
}
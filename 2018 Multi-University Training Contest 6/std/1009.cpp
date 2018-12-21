#include <bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pw(x) (1ll << (x))
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);i++)
#define per(i,l,r) for(int i=(r)-1;i>=(l);i--)
#define dd(x) cout << #x << " = " << (x) << ", "
#define de(x) cout << #x << " = " << (x) << "\n"
#define endl "\n"

//-----
const int N=100005;
pii data[N];
int ans[N],flag[N];
void dfs(int a)
{
    flag[a]=1;
    if(data[a].se)
    {
        if(!flag[data[a].fi])
        {
            dfs(data[a].fi);
            if(ans[data[a].fi]==-1)ans[a]=-1;
            else if(a==ans[data[a].fi])ans[a]=-1;
            else ans[a]=ans[data[a].fi];
        }
        else if(!ans[data[a].fi])ans[a]=N;
        else
        {
            ans[a]=ans[data[a].fi];
            if(ans[a]==a)ans[a]=-1;
        }
    }
    else ans[a]=data[a].fi;
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
        int T;cin>>T;
        while(T--)
        {
            int n;cin>>n;
            rep(i,1,n+1)ans[i]=0,flag[i]=0;
            rep(i,1,n+1)
            {
                int x;string s;cin>>x>>s;
                if(s=="villager")data[i]=mp(x,1);
                else data[i]=mp(x,0);
            }
            rep(i,1,n+1)if(!ans[i])dfs(i);
            int res=0;
            rep(i,1,n+1)res+=ans[i]==-1;
            //rep(i,1,n+1)cout<<ans[i]<<endl;
            cout<<"0 "<<res<<endl;
        }
    return 0;
}
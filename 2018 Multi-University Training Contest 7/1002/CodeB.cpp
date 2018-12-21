#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
struct node{
    int tx, ty, tz;
    node(int x=0, int y=0, int z=0): tx(x), ty(y), tz(z){}
    bool operator < (const node xx) const{
        if(tx != xx.tx) return tx < xx.tx;
        if(ty != xx.ty) return ty < xx.ty;
        return tz < xx.tz;
    }
};
const int maxn = 10010;
int a[3][maxn];
int cnt[3]; char tem[2];
int kin(char x) { return x - 'A';}
int main(){
    int T, posi, n;
    scanf("%d", &T);
    while(T --){
        node ans = node(inf, inf, inf);
        scanf("%d", &n);
        memset(cnt, 0, sizeof(cnt));
        memset(a, 0, sizeof(a));
        int maxv = 0, flag = 0, tmp;
        for(int i = 1; i <= n; i ++){
            scanf("%d%s", &posi, tem);
            a[kin(tem[0])][++cnt[kin(tem[0])]] = posi;
            maxv = max(maxv, posi);
        }
        for(int i = 0; i < 3; i ++){
            a[i][++ cnt[i]] = inf;
        }
        
        for(int i = 1; i <= maxv; i ++){
            int x[3], tx[3];
            for(int j = 0; j < 3; j ++) x[j] = -1, tx[j] = inf;
            
            for(int j = 0; j < 3; j ++){
                /// 暴力算法
                /*
                for(int k = 1; k < cnt[j]; k ++){
                    x[j] = max(x[j], (a[j][k]-1) % i);
                    tx[j] = min(tx[j], (a[j][k]-1) % i);
                    if(x[0] >= tx[1] || x[1] >= tx[2]) break;   
                }
                */

                
                for(int k = (maxv+i-1)/i; k > 0; k --){
                    tmp = *(upper_bound(a[j]+1, a[j]+cnt[j]+1, (k-1)*i));
                    if(tmp <= k*i){
                        tx[j] = min(tx[j], (tmp - 1) % i);
                    }
                    tmp = *(upper_bound(a[j]+1, a[j]+cnt[j]+1, k*i)-1);
                    if(tmp > (k-1)*i){
                        x[j] = max(x[j], (tmp-1) % i);
                    }
                    if(x[0] >= tx[1] || x[1] >= tx[2]) break;
                }
                if(x[0] >= tx[1] || x[1] >= tx[2]) break;
                
            }
            
            
            if(x[0] >= tx[1] || x[1] >= tx[2]) continue;

            flag = 1;
            node anst = node(x[0]+1, x[1]-x[0], i-x[1]-1);
            if(anst < ans)
                ans = anst;
        }
        
        if(flag){
            printf("%d %d %d\n", ans.tx, ans.ty, ans.tz);
        }
        else{
            cout << "NO" << endl;
        }
    }
    return 0;
}
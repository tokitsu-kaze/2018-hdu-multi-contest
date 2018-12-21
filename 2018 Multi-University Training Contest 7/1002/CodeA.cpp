#include<algorithm>
#include<cstdio>
#include<string>
#include<iostream>
#include<cstring>
using namespace std;
const int MAXN = 10100;
int n, m, k, maxv, flag;
int a[3][MAXN], cnt[3];

struct node{
    int x, y, z;
    node(int xt = 0, int yt = 0, int zt = 0) : x(xt), y(yt), z(zt) {}
    bool operator < (const node tx) const{
        if(x != tx.x) return x < tx.x;
        if(y != tx.y) return y < tx.y;
        return z < tx.z;
    }
};



void proc(){
    int T, tem;
    char tc[2];
    scanf("%d", &T);
    while(T --){
        memset(a, 0, sizeof(a));
        memset(cnt, 0, sizeof(cnt));
        node ans = node(MAXN, MAXN, MAXN);
        scanf("%d", &n);
        
        
        
        flag = maxv = 0;
        for(int i = 1; i <= n; i ++){
            scanf("%d%s", &tem, tc);
            int t = tc[0] - 'A';
            a[t][++cnt[t]] = tem;
            maxv = max(maxv, tem);
        }
        a[0][cnt[0]+1] = a[1][cnt[1]+1] = a[2][cnt[2]+1] = MAXN;
        
        for(int i = 1; i <= maxv; i ++){
            int tmp, x = 0, y = MAXN;
            int tx = 0, ty = MAXN;
            for(int j = (maxv+i-1) / i; j > 0; j --){
                tmp = *(upper_bound(a[0]+1, a[0]+1+cnt[0], j*i)-1);
                if(tmp > (j-1)*i) x = max(x, (tmp-1)%i);
                
                tmp = *upper_bound(a[1]+1, a[1]+1+cnt[1], (j-1)*i);
                if(tmp <= j*i)   y = min(y, (tmp-1)%i);
                
                tmp = *(upper_bound(a[1]+1, a[1]+1+cnt[1], j*i)-1);
                if(tmp > (j-1)*i)
                    tx = max(tx, (tmp-1)%i);
                
                tmp = *upper_bound(a[2]+1, a[2]+1+cnt[2], (j-1)*i);
                if(tmp <= j*i)
                    ty = min(ty, (tmp-1)%i);
                
                if(y <= x || ty <= tx)
                    break;
                if(j == 1){
                    node tem = node(x+1, tx-x, i-tx-1);
                    if(tem < ans){
                        ans = tem;
                        flag = 1;
                    }
                }
            }
        }
        if(!flag){
            printf("NO\n");
        }
        else{
            printf("%d %d %d\n", ans.x, ans.y, ans.z);
        }
    }
}


int main(){
    proc(); 
}
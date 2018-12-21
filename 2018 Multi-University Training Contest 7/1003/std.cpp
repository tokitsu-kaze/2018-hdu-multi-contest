#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

#define pass

#define MAXN 120005
#define MAXPOP 10
#define MAXX 10

inline void read(int &x){
    char ch;
    bool flag=false;
    for (ch=getchar();!isdigit(ch);ch=getchar())if (ch=='-') flag=true;
    for (x=0;isdigit(ch);x=x*10+ch-'0',ch=getchar());
    x=flag?-x:x;
}

inline void write(int x){
    static const int maxlen=100;
    static char s[maxlen];
        if (x<0) {   putchar('-'); x=-x;}
    if(!x){ putchar('0'); return; }
    int len=0; for(;x;x/=10) s[len++]=x % 10+'0';
    for(int i=len-1;i>=0;--i) putchar(s[i]);
};

enum {
  PUSH = 's',
  DELETE = 'l',
  POP = 'p',
  QUERY = 'e',
};
#define IDENT(id) cmd[id].op[2]

struct command {
  char op[7];
  int t, x;
} cmd[MAXN];

int popcnt, popt[MAXPOP], popd[MAXPOP], popv[MAXPOP];

int T, N;
int disc[MAXN], dcnt;

int tree[MAXX][MAXN * 4], lazy[MAXX][MAXN * 4];

void push_up(int tree[], int root) {
  tree[root] = max(tree[root * 2], tree[root * 2 + 1]);
}

void push_down(int tree[], int lazy[], int root) {
  if (not lazy[root]) return;
  tree[root * 2 + 0] += lazy[root];
  tree[root * 2 + 1] += lazy[root];
  lazy[root * 2 + 0] += lazy[root];
  lazy[root * 2 + 1] += lazy[root];
  lazy[root] = 0;
}

void update(int l, int r, int v, int tree[], int lazy[], int root, int L, int R) {
  if (l <= L && R <= r) {
    tree[root] += v;
    lazy[root] += v;
    return;
  }
  push_down(tree, lazy, root);
  const int M = (L + R) / 2;
  if (l < M) update(l, r, v, tree, lazy, root * 2 + 0, L, M);
  if (r > M) update(l, r, v, tree, lazy, root * 2 + 1, M, R);
  push_up(tree, root);
}

int find_inrange(int v, int tree[], int lazy[], int root, int L, int R) {
  if (L + 1 == R) return L;
  push_down(tree, lazy, root);
  int M = (L + R) / 2;
  if (tree[root * 2 + 1] > v)
    return find_inrange(v, tree, lazy, root * 2 + 1, M, R);
  if (tree[root * 2 + 0] > v)
    return find_inrange(v, tree, lazy, root * 2 + 0, L, M);
  return -1;
}

int findmore(int t, int v, int tree[], int lazy[], int root, int L, int R) {
  if (L > t) return -1;
  if (R <= t) {
    if (tree[root] > v) {
      return find_inrange(v, tree, lazy, root, L, R);
    } else return -1;
  }
  push_down(tree, lazy, root);
  int M = (L + R) / 2;
  if (M < t) {
    int res = findmore(t, v, tree, lazy, root * 2 + 1, M, R);
    if (res != -1) return res;
  }
  return findmore(t, v, tree, lazy, root * 2 + 0, L, M);
}

int at(int t, int tree[], int lazy[], int root, int L, int R) {
  if (L + 1 == R) return tree[root];
  push_down(tree, lazy, root);
  int M = (L + R) / 2;
  if (t < M)  return at(t, tree, lazy, root * 2 + 0, L, M);
  if (t >= M) return at(t, tree, lazy, root * 2 + 1, M, R);
  return 0;
}

pair<int, int> peaktop(int t) {
  pair<int, int> top = make_pair(-1, -1);
  for (int i = 0; i != MAXX; ++i) {
    int v = at(t, tree[i], lazy[i], 1, 0, dcnt);
    int xtop = findmore(t, v, tree[i], lazy[i], 1, 0, dcnt);
    if (xtop != -1)
      top = max(top, make_pair(xtop, i));
  }
  return top;
}

int query(int t) {
  for (int i = 0; i != popcnt && popt[i] < t; ++i) {
    pair<int, int> pt = peaktop(popt[i] + 1);
    popd[i] = pt.first;
    popv[i] = pt.second;
    if (popd[i] == -1) continue;
	//puts("---------");
    update(0, popd[i] + 1, -1, tree[popv[i]], lazy[popv[i]], 1, 0, dcnt);
  }
  pair<int, int> top = peaktop(t + 1);
  for (int i = 0; i != popcnt && popt[i] < t; ++i) {
    if (popd[i] == -1) continue;
    update(0, popd[i] + 1, +1, tree[popv[i]], lazy[popv[i]], 1, 0, dcnt);
  }
  return top.second;
}


void init() {
	memset(tree,0,sizeof(tree));
	memset(lazy,0,sizeof(lazy));
	memset(disc,0,sizeof(disc));
	memset(popt,0,sizeof(popt));
	memset(popd,0,sizeof(popd));
	memset(popv,0,sizeof(popv));
	dcnt=0;
	popcnt=0;
  //cin >> N;
  scanf("%d",&N);
  for (int i = 0; i != N; ++i) {
  	scanf("%s",cmd[i].op);
    //cin >> cmd[i].op;
    switch (IDENT(i)) {
     case PUSH:
     case DELETE:
     	//scanf("%d%d",&cmd[i].x,&cmd[i].t);
     	read(cmd[i].x);	read(cmd[i].t);
      //cin >> cmd[i].x >> cmd[i].t;
      cmd[i].x -= 1;
      disc[dcnt++] = cmd[i].t;
      break;
     case POP:
     case QUERY:
     	//scanf("%d",&cmd[i].t);
     	read(cmd[i].t);
      //cin >> cmd[i].t;
      disc[dcnt++] = cmd[i].t;
      break;
    }
  }
  sort(disc, disc + dcnt);
  dcnt = unique(disc, disc + dcnt) - disc;
  fill(begin(popd), end(popd), -1);
  popcnt = 0;
}
int fuck_cnt=0;

void work() {
  for (int i = 0; i != N; ++i) {
    int t = lower_bound(disc, disc + dcnt, cmd[i].t) - disc;
    switch (IDENT(i)) {
     case PUSH:
      update(0, t + 1, +1, tree[cmd[i].x], lazy[cmd[i].x], 1, 0, dcnt);
      break;
     case DELETE:
      update(0, t + 1, -1, tree[cmd[i].x], lazy[cmd[i].x], 1, 0, dcnt);
      break;
     case POP:
      popt[popcnt++] = t;
      sort(popt, popt + popcnt);
      break;
     case QUERY:
      {
      	int tmp=query(t) + 1;
      	if (tmp==0)
      		tmp=-1;
	  	fuck_cnt++;
	  	//printf("id = %d  ",fuck_cnt);
	  	printf("%d\n",tmp);
	  	//write(tmp);
	  	//puts("");
	  	//cout<<"id = "<<fuck_cnt<<"  ";
	  	//cout << tmp << "\n";
	  }
      break;
    }
  }
}

int main() {
	//freopen("data.in","r",stdin);
	//freopen("stack1.in","r",stdin);
	//freopen("data.out","w",stdout);
  	//ios_base::sync_with_stdio(false);
  	for (cin >> T; T; --T) {
	    init();
	    work();
  	}
  	//printf("cnt = %d\n",fuck_cnt);
  	//fclose(stdin);	fclose(stdout);
}

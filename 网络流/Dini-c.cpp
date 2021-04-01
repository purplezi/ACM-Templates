#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring> 
#define maxn 10010
#define maxm 10202010
#define Inf 210000000
using namespace std;

struct Edge{
    int u, v, cap, flow;
    int next;
}e[maxn];

int n, m, s, t, ecnt;
int cur[maxn], d[maxn]; 
//cur数组：保存当前节点已经增广到了第几条边，前面的边因为已经增广过，无需再次访问  
//d数组：将图分层之后，每个点的深度 
bool vis[maxn];//bfs中判断是否访问过 
int fi[maxn];

void add_edge(int u, int v, int cap) {
    e[ecnt].u = u, e[ecnt].v = v, e[ecnt].cap = cap, e[ecnt].flow = 0;
    e[ecnt].next = fi[u], fi[u] = ecnt;
    ecnt++;
}   //邻接表 

bool bfs() {
    memset(vis, 0, sizeof(vis));
    int q[maxn], head = 0, tail = 1;
    q[0] = s;
    d[s] = 0;
    vis[s] = 1;
    while(head < tail) {
        int x = q[head++];
        for(int i = fi[x]; i != -1; i = e[i].next)
            if(!vis[e[i].v] && e[i].flow < e[i].cap) {
                vis[e[i].v] = 1;
                d[e[i].v] = d[x] + 1;
                q[tail++] = e[i].v;
            }
    }
    return vis[t];
}//一个普通的bfs，每一次建出一个能连接到t的分层图

int dfs(int x, int a) { // x：当前访问到那个节点 a：至今为止，最小残量是多少
    if(x == t || a == 0) return a;
    int flow = 0, f;    //flow到当前的最大增广流， f为其子节点的最大增广流 
    for(int& i = cur[x]; i != -1; i = e[i].next)
        if(d[x] + 1 == d[e[i].v] && (f = dfs(e[i].v, min(a, e[i].cap - e[i].flow))) > 0) {
            e[i].flow += f;
            e[i^1].flow -= f;
            flow += f;
            a -= f;
            if(a == 0) break;
        }
    if(a)
        d[x] = -1;   //神奇而高效的优化
    return flow;
}

int max_flow() {
    int ans = 0;
    while(bfs()) {
        memcpy(cur, fi, sizeof(fi));    //将cur数组初始为每一个点的第一条出边 
        ans += dfs(s, Inf);
    }
    return ans;
}

int main() {
    memset(fi, -1, sizeof(fi));
    scanf("%d%d", &n, &m);
    s = 1, t = n;
    for(int i = 1; i <= m; i++) {
        int u, v, cap;
        scanf("%d%d%d", &u, &v, &cap);
        add_edge(u, v, cap);
        add_edge(v, u, 0);
    }
    int ans = max_flow();
    printf("%d", ans);
    return 0;
}
# include <iostream>
# include <stdio.h>
# include <string.h>
# include <algorithm>
# include <math.h>
# include <queue>
# include <string>
# include <vector>
# include <set>
# include <map>
# define INF 0x3f3f3f3f
# define clr0(x) memset(x,0,sizeof(x))
# define clr1(x) memset(x,INF,sizeof(x))
# define clrf(x) memset(x,-1,sizeof(x))
# define rep(i,a) for(int i = 0;i<(a);i++)
# define repf(i,a,b) for(int i = (a);i<=(b);i++)
# define repu(i,a,b) for(int i = (a);i<(b);i++)
# define repd(i,a,b) for(int i = (a);i>=(b);i--)
# define lowbit x&(-x)
# define ww(a) while(a)
# define sc(x) scanf("%d",&(x))
# define sl(x) scanf("%I64d",&(x))
# define pc(x) printf("%d\n",(x));
# define pl(x) printf("%I64d\n",(x));
# define wT() int T;scanf("%d",&T);while(T--)
# define wt() int T;scanf("%d",&T);for(int tt = 1;tt<=T;tt++)
# define lson(x) (x)<<1
# define rson(x) (x)<<1|1
# define ll long long
# define fuckio ios::sync_with_stdio(false);
# define fuck cout<<"fuck:"<<__LINE__<<endl;
# define maxn 220

using namespace std;

int G[maxn][maxn],flow[maxn],pre[maxn];
int n,m;
queue<int>q;
int bfs(int s,int t)
{
    ww(!q.empty())q.pop();
    clrf(pre);
    pre[s] = 0;flow[s] = INF;
    q.push(s);
    ww(!q.empty()){
        int p = q.front();
        q.pop();
        if(p == t){
            break;
        }
        repf(u,1,n){
            if(u!=s&&G[p][u]>0&&pre[u] == -1){
                pre[u] = p;
                flow[u] = min(G[p][u],flow[p]);
                q.push(u);
            }
        }
    }
    if(pre[t] == -1)return -1;
    return flow[t];
}
int Ek(int s,int t)
{
    int delta = 0;//当前残余网络更新多少
    int tot = 0;
    ww(1){
        delta = bfs(s,t);
        if(delta == -1)break;//bfs找不到增广路
        int p = t;
        ww(p!=s){
            G[pre[p]][p] -= delta;
            G[p][pre[p]] += delta;
            p = pre[p];
        }
        tot += delta;
    }
    return tot;
}
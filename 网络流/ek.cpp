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
# define maxn 420

using namespace std;

struct Edge{
    int from,to,cap,flow;
    Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f){}
};

struct EK{
    int m;
    vector<Edge>edges;
    vector<int>G[maxn];
    int a[maxn];
    int p[maxn];

    void init(int n){
        repf(i,0,n)G[i].clear();
        edges.clear();
    }
    void addedge(int from,int to,int cap){
        edges.push_back(Edge(from,to,cap,0));
        edges.push_back(Edge(to,from,0,0));
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    int maxflow(int s,int t){
        int flow = 0;
        ww(1){
            clr0(a);
            queue<int>Q;
            Q.push(s);
            a[s] = INF;
            ww(!Q.empty()){
                int x = Q.front();
                Q.pop();
                rep(i,G[x].size()){
                    Edge &e = edges[G[x][i]];
                    if(!a[e.to]&&e.cap-e.flow>0){
                        p[e.to] = G[x][i];
                        a[e.to] = min(a[x],e.cap-e.flow);
                        Q.push(e.to);
                    }
                }
                if(a[t])break;
            }
            if(!a[t])break;
            for(int u = t;u!=s;u = edges[p[u]].from){
                edges[p[u]].flow += a[t];
                edges[p[u]^1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }
}ek;

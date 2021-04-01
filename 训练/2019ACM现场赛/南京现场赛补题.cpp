#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int maxn=1005;
const int MAXN=1e6+5;
const int mod=1e9+7;
int mp[maxn][maxn],n,m,deg[MAXN],val[maxn][maxn],vis[MAXN];
ll dp[MAXN][5];
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
vector<int> tr[maxn];
ll ans;
queue<int> q;
int jud(int x,int y){
	if(x>=0&&x<n&&y>=0&&y<m)return 1;
	return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			scanf("%d",&mp[i][j]);
			val[i][j]=i*m+j;
		}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			for(int k=0;k<4;k++){
				int tx=i+dir[k][0];
				int ty=j+dir[k][1];
				if(jud(tx,ty)&&mp[tx][ty]==mp[i][j]+1){
					tr[val[i][j]].push_back(val[tx][ty]);
					deg[val[tx][ty]]++;
				}
			}
		}
	}
	for(int i=0;i<n*m;i++){
		if(!deg[i]){
			q.push(i);
			dp[i][1]=1;
		}
	}
	while(!q.empty()){
		int tmp=q.front();q.pop();
		if(tr[tmp].size()==0) ans=(ans+dp[tmp][4])%mod;
		for(int i=0;i<tr[tmp].size();i++){
			int tm=tr[tmp][i];
			deg[tm]--;
			if(!deg[tm])q.push(tm);
			dp[tm][2]=(dp[tm][2]+dp[tmp][1])%mod;
			dp[tm][3]=(dp[tm][3]+dp[tmp][2])%mod;
			dp[tm][4]=(dp[tm][4]+dp[tmp][3]+dp[tmp][4])%mod;
		}
	}
	printf("%lld\n",ans);
	return 0;
} 

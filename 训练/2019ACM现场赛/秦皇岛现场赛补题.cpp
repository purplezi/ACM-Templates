//D
//#include<stdio.h>
//#include<iostream>
//using namespace std;
//int t,n;
//int main(){
//	scanf("%d",&t);
//	while(t--){
//		scanf("%d",&n);
//		while(n%2==0){
//			n/=2;
//		}
//		while(n%5==0){
//			n/=5;
//		}
//		if(n>1)puts("Yes");
//		else puts("No");
//	}
//	return 0;
//}

//F
//思路：1.找环上的边 2.乘起来
//分别找每一个连通块  
#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 5e5 + 5;
const int mod = 998244353;
int n, m, u, v, vis[maxn], stp[maxn], cnt;
ll ans;
vector<int> mp[maxn];
ll qPow(ll a, ll n) {
	ll ans = 1;
	while (n) {
		if (n & 1)ans = ans * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return ans % mod;
}
void dfs(int st, int pre, int dis) {
	vis[st] = 1;
	for (int i = 0; i < mp[st].size(); i++) {
		if (mp[st][i] == pre)continue;
		if (vis[mp[st][i]]) {
			if (stp[mp[st][i]]<stp[pre]) {//防止dfs回溯的时候 又加一遍
				cnt += dis + 1 - stp[mp[st][i]];
				ans = ans * (qPow(2, dis + 1 - stp[mp[st][i]]) - 1 + mod) % mod;
			}
			
		}
		else {
			stp[mp[st][i]] = dis + 1;
			dfs(mp[st][i], st, stp[mp[st][i]]);
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	ans = 1; cnt = 0;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &u, &v);
		mp[u].push_back(v);
		mp[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			stp[i] = 0;
			dfs(i, i, stp[i]);
		}
	}
	ans = ans * qPow(2, m - cnt) % mod;
	printf("%lld\n", ans);
	return 0;
}

/*
5 6
1 2
1 3
2 3
3 5
3 4
4 5
49
*/

/*
6 7
1 2
1 3
2 3
3 4
4 6
4 5
5 6
98

3 3
1 2
2 3
3 1
7

6 6
1 2
2 3
3 1
2 4
4 5
5 2
49
*/



////I 
////上一个的字符串的尾数，要和下一个字符串的起始尽量的切合 
//#include<stdio.h>
//#include<iostream>
//#include<map>
//#include<string.h>
//using namespace std;
//const int maxn=1e5+5; 
//string ss;
//map<char,string> mp;
//int tmp,dp[maxn][6];//第i个值时的方案数 
//string s[6];
//int pos[6][3]={{0,1,2},{0,2,1},{1,0,2},{2,0,1},{1,2,0},{2,1,0}};
//int main(){
//	mp['Y']="QQQ";mp['V']="QQW";mp['G']="QQE";
//	mp['C']="WWW";mp['X']="QWW";mp['Z']="WWE";
//	mp['T']="EEE";mp['F']="QEE";mp['D']="WEE";mp['B']="QWE";
//	memset(dp,0x3f,sizeof(dp));
//	cin>>ss;
//	int len=ss.length();
//	//初始化
//	for(int i=0;i<6;i++)dp[0][i]=3;
//	for(int i=1;i<len;i++){	
//		//当前的和上6种判断
//		int minn=0x3f3f3f3f;	
//		for(int j=0;j<6;j++){
//			for(int k=0;k<6;k++){
//				//三个判断
//				if(mp[ss[i]][pos[j][0]]==mp[ss[i-1]][pos[k][0]]&&mp[ss[i]][pos[j][1]]==mp[ss[i-1]][pos[k][1]]&&mp[ss[i]][pos[j][2]]==mp[ss[i-1]][pos[k][2]])tmp=3;
//				else if(mp[ss[i]][pos[j][0]]==mp[ss[i-1]][pos[k][1]]&&mp[ss[i]][pos[j][1]]==mp[ss[i-1]][pos[k][2]])tmp=2;
//				else if(mp[ss[i]][pos[j][0]]==mp[ss[i-1]][pos[k][2]])tmp=1;
//				else tmp=0; 
//				dp[i][j]=min(dp[i][j],dp[i-1][k]+3-tmp);
//			} 
//		}
//	}
//	int ans=0x3f3f3f3f;
//	for(int i=0;i<6;i++)ans=min(ans,dp[len-1][i]);
//	printf("%d\n",ans+len);
//	return 0;
//}

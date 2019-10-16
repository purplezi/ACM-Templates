# ACM板子和总结

## 1.线段树与树状数组

### 树状数组

单点修改区间更新（区间是指1-k的区间）、区间查询，所有要得到区间值的时候可以对两个区间用减法。

``` c++
ll c[maxn];

int lowbit(int x){//返回二进制最小的bit那一位
	return x&-x;
}

void add(int x,ll val){//单点修改，区间更新
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]=max(c[i],val);
	}
}

ll query(int x){//查询1-x的值
	ll ans=0;
	for(int i=x;i>0;i-=lowbit(i)){
		ans=max(ans,c[i]);
	}
	return ans;
}
```



### 线段树

区间、单点修改，区间、单点查询（任意区间），通过模板的函数改变参数即可。

```c++
#define lson rt << 1	  // == rt * 2	 左儿子
#define rson rt << 1 | 1  // == rt * 2 + 1 右儿子
#define int_mid int mid = tree[rt].l + tree[rt].r >> 1
int a[maxn];
int n;
 
struct node {
	int l, r;
//	ll val, lazy;
	int val,lazy; 
} tree[maxn * 4];
 
void push_up(int rt) {
	tree[rt].val = min(tree[lson].val, tree[rson].val);
	//tree[rt].val = max(tree[lson].val, tree[rson].val);//最大值 
//	tree[rt].val = tree[lson].val + tree[rson].val;//累加和 
}
 
void push_down(int rt) {
	if (tree[rt].lazy) {
		tree[lson].lazy += tree[rt].lazy;
		tree[rson].lazy += tree[rt].lazy;
		// 维护最大最小值
			tree[lson].val += tree[rt].lazy;
			tree[rson].val += tree[rt].lazy;
		//
		 // 维护和
//			int l = tree[rt].l, r = tree[rt].r;
//			int mid = l + r >> 1;
//			tree[lson].val += 1ll * (mid - l + 1) * tree[rt].lazy;
//			tree[rson].val += 1ll * (r - mid) * tree[rt].lazy;
		tree[rt].lazy = 0;
	}
}
 
void build(int rt, int l, int r) { // 建树
	tree[rt].l = l, tree[rt].r = r;
	tree[rt].lazy = 0;
	if (l == r) {
		tree[rt].val = a[l]; // 给定一个初始值
		return;
	} else {
		int mid = l + r >> 1; // (l + r) / 2
		build(lson, l, mid);
		build(rson, mid + 1, r);
		push_up(rt);
	}
}
 
void update_point(int rt, int pos, ll val) { // 单点更新
	if (tree[rt].l == tree[rt].r && pos == tree[rt].l) {
		tree[rt].val = val;
		return;
	}
	int_mid;
	if (pos <= mid) update_point(lson, pos, val);
	else update_point(rson, pos, val);
	push_up(rt);
}
 
void update_interval(int rt, int l, int r, ll val) { // 区间更新
	if (l <= tree[rt].l && r >= tree[rt].r) {
		tree[rt].lazy += val;
		tree[rt].val = val; // 维护最大最小值
//		tree[rt].val += 1ll * (tree[rt].r - tree[rt].l + 1) * val; // 维护和 
		return;
	}
	push_down(rt);
	int_mid;
	if (l <= mid) update_interval(lson, l, r, val);
	if (r > mid) update_interval(rson, l, r, val);
	push_up(rt);
}
 
int query_point(int rt, int pos) { // 单点查询
	if (tree[rt].l == tree[rt].r && tree[rt].l == pos)
		return tree[rt].val;
	push_down(rt);
	int_mid;
	if (pos <= mid) query_point(lson, pos);
	else query_point(rson, pos);
}
 
int query_interval(int rt, int l, int r) { // 区间查询
	if (l <= tree[rt].l && r >= tree[rt].r)
		return tree[rt].val;
	push_down(rt);
	int_mid;
	if (r <= mid) return query_interval(lson, l, r);
	else if (l > mid) return query_interval(rson, l, r);
	else {
		return min(query_interval(lson, l, mid), query_interval(rson, mid + 1, r));
		//return max(query_interval(lson, l, mid), query_interval(rson, mid + 1, r));//维护最大值 
//		return query_interval(lson, l, mid) + query_interval(rson, mid + 1, r);//维护总和 
	}
}
```



**注意：如果是处理的是连续性问题，比如贴海报,用区间代表一张海报（如0-1），需要特殊处理：建树的时候不需要mid+1，树的叶子节点应该是0-1、1-2、2-3……，在区间更新和区间查询的时候，当tree[rt].l+1==tree[rt].r的时候就是到达了叶子结点，这个时候需要写一个if进行return，不能再继续搜下去。**

字符串的区间更新和查找可以用二进制来进行转换处理。

## 2.网络流

## 3.高精度计算

如果遇到卡常了，尝试加快输入时间，使用输入输出外挂。

```c++
int Scan()///输入外挂
{
    int res=0,ch,flag=0;
    if((ch=getchar())=='-')
        flag=1;
    else if(ch>='0'&&ch<='9')
        res=ch-'0';
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+ch-'0';
    return flag?-res:res;
}

void Out(LL a)///输出外挂
{
    if(a>9)
        Out(a/10);
    putchar(a%10+'0');
}
```





## 4.最短路和最小生成树

## 5.计算几何

## 6.博弈

## 7.数论

组合数学：

错排公式：n个数全部错开排序种类数

```
D(n)=n!/e+0.5(e自然常数)
```



## 8.RMQ和LCA

维护区间最值，dp\[i][j]=是指从第i位连续第$2^j$个数（i—i+$ 2^j $-1）区间内的最值。

先初始化后用函数查询使用（感觉线段树更方便）

```c++
void rmq_init()
{
    for(int i=1;i<=N;i++)
        dp[i][0]=arr[i];//初始化
    for(int j=1;(1<<j)<=N;j++)//j判断长度
        for(int i=1;i+(1<<j)-1<=N;i++)//i判断位置,终止位置不能超过长度N
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<j-1)][j-1]);
}
```

```c++
int rmq(int l,int r)
{
    int k=log2(r-l+1);
    return min(dp[l][k],dp[r-(1<<k)+1][k]);
}
```



LCA:最近公共祖先，当处理距离的时候，树上差分的时候会有效。

```c++
const int maxn = 2e5 + 10;

int depth[maxn] = { 0 };
int father[maxn][22];
int lg[maxn];
int n;

const int maxm = maxn * 2;
int top = 0;
int head[maxn];

struct Edge {
	int to, w, next;
}edge[maxm];

void init() {
	top = 0;
	for (int i = 0; i < maxn; ++i) {
		head[i] = -1;
	}
	lg[0]=-1;
        for(int i=1;i<=n;i++)lg[i]=lg[i>>1]+1;
    lg[0]=0;
}

void addedge(int u, int v, int w) {
	edge[top].w = w;
	edge[top].to = v;
	edge[top].next = head[u];
	head[u] = top++;
	edge[top].w = w;
	edge[top].to = u;
	edge[top].next = head[v];
	head[v] = top++;
}//???

void dfs(int u, int fa) {
	depth[u] = depth[fa] + 1;
	father[u][0] = fa;
	for (int i = 1; (1 << i) <= depth[u]; ++i) {
		father[u][i] = father[father[u][i - 1]][i - 1];
	}

	for (int i = head[u]; i != -1; i = edge[i].next) {
		int to = edge[i].to;
		if (to != fa)
			dfs(to, u);
	}
}


int lca(int x, int y) {
	if (depth[x] < depth[y])	swap(x, y);
	while (depth[x] > depth[y]) x = father[x][lg[depth[x] - depth[y]]];
	if (x == y)	return x;
	for (int k = lg[depth[x]]; k >= 0; --k) {
		if (father[x][k] != father[y][k]) {
			x = father[x][k];
			y = father[y][k];
		}
	}

	return father[x][0];
}
```



树上差分

```c++
int dfs2(int u,int fa){
	int num=0;
	for (int i = head[u]; i != -1; i = edge[i].next) {
		int to = edge[i].to;
		if (to != fa)
			num+=dfs2(to, u);
	}
	return num+sz[u];
} 

main(){
    int l=lca(x,y);
	sz[l]--;
	sz[father[l][0]]--;
}
```



## 9.概率DP和数位DP

### 概率DP

* 期望的概念：

![1570856128899](C:\Users\HBlade\AppData\Roaming\Typora\typora-user-images\1570856128899.png)

* 性质
    1. E(c)=0，其中c为任意常数
    2. E(a\*X)=a*E(X)，其中a为任意常数。
    3. E(a\*X+b\*Y)=a\*E(X)+b*E(Y)，期望的线性性 

例题1：n个格子，每次随机涂一个，求涂满m个格子的期望次数

dp\[i]表示剩下i个格子没涂的时候，涂满这些格子的期望次数。首先dp[0]=0；

转移方程：dp[i]=(n-i/n)dp[i]+(i/n)dp[i-1]+1 

意思：因为有n-i个格子已经被涂过了，所以有((n-i)/n)的概率涂到已经涂过的格子；同理还有(i/n)的概率涂到没有涂过的格子。+1是因为无论涂了哪种格子，次数都得加一，得到转移方程。左右整理式子得：

dp[i]=(n+i)/i*dp[i-1]



例题2：n个格子，每次随机涂一个，求涂满m次后的期望涂色格子数。

设dp[i]表示涂i次以后期望涂了格子数，有dp[0]=0。

dp[i+1]=dp[i]+(n-dp[i])/n*1

dp[i+1]=dp[i]+(n-dp[i])/n*1

再涂一次，有(n-dp[i])/n的概率再多涂一个，所以是在原有的dp[i]的基础上加上一个pk*w(pk是概率，w是贡献，该题贡献是多一个棋子)



例题3：有n(n<=20)个格子，每次会涂一个格子，其中涂第i个格子的概率是p_i（保证∑p_i=1）。求每个格子都被涂色的期望次数。（类似的例题：HDU 4336）

状压dp+概率：二进制1认为当前格子已经被涂色。dp[1<<n-1]=0,dp[0]为所求的答案。

转移：从0开始转移。

```c++
int m=(1<<n)-1;
dp[m]=0;
for(int i=m-1;i>=0;i--){
    double tmp=1;double x=1;
	for(int j=0;j<n;j++){
		if(i&(1<<j)) x-=p[j];
        else tmp+=p[j]*dp[i|(1<<j)];
    }
    dp[i]=tmp/x;
}
cout<<dp[0]<<endl;
```

```c++
int sum=(1<<n)-1;
dp[sum]=0;//涂满的期望次数为0
for(int i=sum-1;i>=0;i--){
	dp[i]=1;
	double tmp=0;
	for(int j=0;j<n;j++){
		if((i&(1<<j))==0){
			dp[i]+=dp[i+(1<<j)]*p[j];
			tmp+=p[j];
		}
	}
	dp[i]/=tmp;
}
cout<<dp[0]<<endl;
```

概率dp的一般递推式：

```
dp[i]=Σ𝑝[𝑖→𝑗]∗𝑑𝑝[𝑗]+𝑤[𝑖→𝑗] 
其中dp[i]表示当前状态为i的期望（自己定义的）
𝑝[𝑖→𝑗]表示从状态i到状态j的概率
𝑤[𝑖→𝑗] 表示从状态i到状态j转移的时候对答案的贡献
```

* 期望的线性性
	* 随机游走(链和图)
	1. 一个长度为n的链，从一端走到另一端的期望时间？设dp[i]表示从i第一次到i+1所需要的期望时间，则dp[i]=1/2+1/2*(1+dp[i-1]+dp[i]) 得dp[i]=dp[i-1]+2。dp[1]=1（1到2只能前进）。ans=dp[1]+dp[2]+……+dp[n-1]=(n-1)^2

	2. N个点的完全图，问从S走到T的期望时间？ans=1/(n-1)+(n-2)/(n-1)\*(ans+1)得1/(n-1)*ans=1得ans=n-1。


### 数位DP

根据数的情况进行dp，使用记忆化搜索。

模板题：求a~b中不包含4和62的数的个数。dp\[i][j]：i代表前i位，j代表前一个数是否出现6

```c++
#include<bits/stdc++.h>
using namespace std;

const int maxn=2e4+5;

typedef long long ll;

ll dp[20][2];

int a[20];

ll dfs(int pos,bool limit,bool lead,bool status){
	if(pos==-1) return 1;
	if(!limit&&!lead&&dp[pos][status]!=-1) return dp[pos][status];
	int up=limit?a[pos]:9;
	ll ans=0;
	for(int i=0;i<=up;i++){
		if(i==4) continue;
		if(status&&i==2) continue;
		ans+=dfs(pos-1,limit&&i==a[pos],lead&&i==0,i==6);
	}
	if(!limit&&!lead) dp[pos][status]=ans;//有前导0和上限限制的情况下不能被记忆化搜索
	return ans;
}

ll solve(ll x){
	memset(dp,-1,sizeof(dp));
	int pos=-1;
	while(x){
		a[++pos]=x%10;
		x/=10;
	}
	return dfs(pos,1,1,0);
}

int main(){
	ll l,r;
	while(cin>>l>>r){
		if(l==0&&r==0) break;
		cout<<solve(r)-solve(l-1)<<endl;
	}
	return 0;
}
```

* 条件概率
  * 在已知事件B发生的条件下，A发生的概率，记为P(A|B)。计算公式：P(A|B)=P(AB)/P(B)
  * 全概率公式：P(A)=P(B1)xP(A|B1)+…+P(Bn)xP(A|Bn)。B1,…,Bn是互不相容的事件，且U(B1,…,Bn)=全集Ω


## 10.图论算法

## 11.Hash字符串和马拉车

### Hash字符串模板

```c++
typedef unsigned long long ull;
const ull base=233;
const int maxn=400010;
ull p[maxn],hs[maxn];
void Insert(char s[]){
    int len=strlen(s);
	hs[0]=s[0];
    for(int i=1;i<len;i++)
    {
        hs[i]=hs[i-1]*base+(ull)s[i];
    }
    p[0]=1;
    for(int i=1;i<=len;i++){
   		p[i]=p[i-1]*base;
    }
}

ull GetHash(int l,int r){
	return (ull)hs[r]-p[r-l+1]*hs[l-1];
}
```

Hash字符串，使用值代表一段字符串，当判断两段字符串是否相等的时候可以考虑是否使用Hash字符串。

输入完s字符串后，使用Insert函数来处理成字符串Hash，搜索一段长度的Hash值时，使用GetHash函数。



### 马拉车

模板：

```c++
int Len[3000005];  
char str[3000005],s[3000005];  
int n,mx,id,len;  

void init(){  
    int k=0;  
    str[k++] = '$';  
    for(int i=0;i<len;i++){  
        str[k++]='#';  
        str[k++]=s[i];  
    }  
    str[k++]='#';  
    len=k;  
}  

int Manacher(){  
	Len[0] = 0;  
	int sum = 0;  
	mx = 0;  
	for(int i=1;i<len;i++){  
	if(i < mx) Len[i] = Min(mx - i, Len[2 * id - i]);  
	else Len[i] = 1;  
	while(str[i - Len[i]]== str[i + Len[i]]) Len[i]++;  
        if(Len[i] + i > mx){  
          mx = Len[i] + i;  
          id = i;  
          sum = Max(sum, Len[i]);  
        }  
	}
	return (sum - 1);  
}  
```





## 12.KMP和AC自动机



## 13.Python

多组输入

```python
while True:
    try:
        a,b = map(int,input().split())
        print(a+b)
    except:
        break
```

普通输入

```python
d=int(input())#整数输入
f=float(input())#浮点数输入
s=input()#字符串输入
```

T输入：

```python
T=int(input())
while T>0:
    d=int(input())
    T-=1
```

空格输入数组：

```python
n=int(input())
m=int(input())
a=[]
for i in range(0,n):
	k=input().split()#k是数组
```

排序:

```python
list.sort(cmp=None, key=None, reverse=False)
a.sort(lambda x:x[0]*x[1])#lambda表达式 放在cmp位置，相当于一条表达式
```

- cmp -- 可选参数, 如果指定了该参数会使用该参数的方法进行排序。
- key -- 主要是用来进行比较的元素，只有一个参数，具体的函数的参数就是取自于可迭代对象中，指定可迭代对象中的一个元素来进行排序。
- reverse -- 排序规则，**reverse = True** 降序， **reverse = False** 升序（默认）。



输出：

```python
print('a',end=' ')#end默认为回车，需要输出后面跟空格需要修改end
print('%.3d'%sum)#和C语言差不多，但是','要改成','
```



一些函数:

split:

```python
str.split(str="", num=string.count(str)).
```

- str -- 分隔符，默认为所有的空字符，包括空格、换行(\n)、制表符(\t)等。
- num -- 分割次数。默认为 -1, 即分隔所有。



strip:

```python
str.strip(' ')
```

* 返回移除字符串头尾指定的字符生成的新字符串。 



replace:

```python
str.replace(old,new,mx)
```

- old -- 将被替换的子字符串。
- new -- 新字符串，用于替换old子字符串。
- max -- 可选字符串, 替换不超过 max 次

## 其他

### 约瑟夫环

```c++
f[1]=0;
for(int i=2;i<=n;i++){
    f[i]=(f[i-1]+m)%i;//第m个被杀掉
}
printf("%d",f[k]+1)//输出
//相当于从最后往前递推，知道最后一个人是谁活着，那就知道他前一个人是谁，一直往前递推即可，中间对i取模的意思是当只有i个人的时候，不能超过人数所以要取模。
```



### 卡特兰数

其前几项为（从第0项开始） : 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190, 6564120420, 24466267020, 91482563640, 343059613650, 1289904147324, 4861946401452, ... 

 其前几项为（从第零项开始） : 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190, 6564120420, 24466267020, 91482563640, 343059613650, 1289904147324, 4861946401452, ... 

递推式：

 ![img](https://gss1.bdstatic.com/9vo3dSag_xI4khGkpoWK1HF6hhy/baike/pic/item/f9dcd100baa1cd11b39fb131b712c8fcc3ce2df2.jpg) 

 ![img](https://gss1.bdstatic.com/9vo3dSag_xI4khGkpoWK1HF6hhy/baike/pic/item/ac4bd11373f082027bb2607341fbfbedab641b5d.jpg) 

 **h(n)=h(n-1)\*(4\*n-2)/(n+1);** 

题目类型：

**括号化**

矩阵连乘： P=a1×a2×a3×……×an，依据乘法结合律，不改变其顺序，只用括号表示成对的乘积，试问有几种括号化的方案？(h(n)种) 

**出栈次序**

一个栈(无穷大)的进栈序列为1，2，3，…，n，有多少个不同的出栈序列?

选择k作为最后一个输出的数，在k之前有k-1个数，有f(k-1)种可能，在k之后有n-k个数，有f(n-k)个可能，
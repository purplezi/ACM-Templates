## 对拍程序
* #### ModifyInput.cpp(修改输入：input.txt)
* #### Mypro.cpp(自己写的程序，输入来自input.txt,输出到output.txt)
* #### Sol.cpp(标准答案或暴力解决的方案，输入来自 input.txt,输出到 ans.cpp)
* #### Random.cpp(运行程序测试点)
  

##### ModifyInput.cpp
```c++
int random(int n)//返回0到n-1之间的随机整数，若要负数则先产生0到2n的随机整数再减n，这里保证返回的都是int
{
	return (long long)rand()*rand() % n;//产生0--n-1的随机数
}

int a[1000000];
int main()
{
	srand((unsigned)time(0));
	freopen("E:\\programmme\\ACM\\Template\\infercheck\\Random\\input.txt", "w", stdout);
	//随机生成序列(n<=1e5,绝对值在1e6之内的整数）
	int n = random(100000) + 1;
	printf("%d\n", n);
	int m = 1000000;
	for (int i = 1; i <= n; i++)
	{
		a[i] = random(2 * m + 1) - m;
		printf("%d\n",a[i]);
	}
	

	//随机生成序列（随机生成m个[1,n]的子区间）
	int m = random(10) + 1;
	int n = random(100000) + 1;
	for (int i = 1; i <= m; i++)
	{
		int l = random(n) + 1;
		int r = random(n) + 1;
		if (l > r)
		{
			swap(l, r);
		}
		printf("%d %d\n", l, r);
	}

	//随机生成树(随机生成一棵n个点的树，用n个点n-1条边的无向图形式输出，每条边带一个1e9以内正整数权值)
	int n = random(100000) + 1;
	for (int i = 2; i <= n; i++)
	{
		int fa = random(i - 1) + 1;
		int val = random(1000000000) + 1;
		printf("%d %d %d\n", fa, i, val);
	}

	//随机生成图(随机生成一张n个点m条边的无向图，图中不存在重边、自环，且必须连通，保证5<=n<=m<=n*(n-1)/4<=1e6)
	vector<pair<int,int>> e;//保存数据
	map<pair<int, int>, bool> h;//防止重边
	//先生成一棵树，保证连通
	int n = random(100) + 1;
	printf("%d ", n);
	e.push_back(make_pair(0, 0));
	for (int i = 1; i < n; i++)
	{
		int fa = random(i) + 1;
		e.push_back(make_pair(fa, i + 1));
		h[e[i]] = h[make_pair(i + 1, fa)] = 1;
	}
	//再生成剩余的m-n+1条边
	int m = random(n*(n -1)/4) + 1;
	printf("%d\n", m);
	for (int i = n; i <= m; i++)
	{
		int x, y;
		do
		{
			x = random(n) + 1;
			y = random(n) + 1;
		} while (x == y || h[make_pair(x, y)]);
		e.push_back(make_pair(x, y));
		h[e[i]] = h[make_pair(y, x)] = 1;
	}
	//随机打乱，输出
	random_shuffle(e.begin()+1, e.begin()+ m + 1);
	for (int i = 1; i <= m; i++)
	{
		printf("%d %d\n", e[i].first, e[i].second);
	}

	int t = random(3) + 1;
	printf("%d\n", t);
	while (t--)
	{
		int n = random(1000) + 1;
		for (int i = 1; i <= n; i++)
		{
			a[i] = random(1e5) + 1;
			if (i != n)
			{
				printf("%d ", a[i]);
			}
			else
			{
				printf("%d\n", a[i]);
			}			
		}
		int m = random(100) + 1;
		for (int i = 1; i <= m; i++)
		{
			int m1 = random(1e5) + 1;
			int m2 = random(10) + 1;
			printf("%d %d\n", m1, m2);
		}
	}
	//system("pause");
	return 0;
}
```

##### Mypro.cpp
```c++
...
int main()
{
	freopen("E:\\programmme\\ACM\\Template\\infercheck\\Random\\input.txt", "r", stdin);
	freopen("E:\\programmme\\ACM\\Template\\infercheck\\Random\\output.txt", "w", stdout);
...//自己写的解决程序
}
```


##### Sol.cpp
```c++
...
int main()
{
	freopen("E:\\programmme\\ACM\\Template\\infercheck\\Random\\input.txt", "r", stdin);
	freopen("E:\\programmme\\ACM\\Template\\infercheck\\Random\\ans.txt", "w", stdout);
...//暴力或答案写的解决程序
}
```


##### Random.cpp
```c++
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;

int main()
{
	for (int T = 1; T <= 1000; T++)
	{
		system("E:\\programmme\\ACM\\Template\\infercheck\\ModifyInput\\Debug\\ModifyInput.exe");
		double st = clock();
		system("E:\\programmme\\ACM\\Template\\infercheck\\Mypro\\Debug\\Mypro.exe");
		double ed = clock();
		system("E:\\programmme\\ACM\\Template\\infercheck\\Sol\\Debug\\Sol.exe");
		if (system("fc E:\\programmme\\ACM\\Template\\infercheck\\Random\\output.txt E:\\programmme\\ACM\\Template\\infercheck\\Random\\ans.txt"))
		{
			puts("Wrong Answer");
			system("pause");
			return 0;
		}
		else
		{
			printf("Accepted,测试点 #%d,用时 %.01fms\n", T, ed - st);
		}
	}
	system("pause");
	return 0;
}
```
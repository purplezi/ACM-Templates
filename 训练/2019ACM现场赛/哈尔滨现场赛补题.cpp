// I Interesting Permutation
#include<stdio.h>
#include<iostream>
using namespace std;
const int maxn=1e5+5;
const int mod=1e9+7;
typedef long long ll;
ll ans;
int n,t,a[maxn],tmp;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		tmp=0;ans=1;
		for(int i=0;i<n;i++)scanf("%d",&a[i]);
		if(a[0]!=0||a[n-1]!=n-1){
			puts("0");continue;
		}
		int flg=0;
		for(int i=1;i<n;i++){
			if(a[i]>a[i-1]){
				ans=(ans*2)%mod;
				tmp+=(a[i]-a[i-1]-1);
			}
			else if(a[i]==a[i-1]){
				if(tmp==0){
					flg=1;break;
				}
				ans=(ans*tmp)%mod;
				tmp--;
			}
			else{
				flg=1;break;
			}
		}
		if(flg)puts("0");
		else printf("%lld\n",ans);
	}
	return 0;
}

// J Jsutifying the Conjecture
#include<stdio.h>
#include<iostream>
using namespace std;
int t,n;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		if(n<=5)puts("-1");
		else if(n%2==0) printf("%d %d\n",2,n-2);
		else printf("%d %d\n",3,n-3);
	}
	return 0;
} 

//  k Keeping Rabbits
#include<stdio.h>
#include<iostream>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
int t,n,k,w[maxn]; 
double pos[maxn];
ll sum;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		sum=0;
		for(int i=0;i<n;i++){
			scanf("%d",&w[i]);
			sum+=w[i];
		}
		for(int i=0;i<n;i++){
			pos[i]=1.0*w[i]/sum;
		}
		for(int i=0;i<n;i++){
			printf("%.05lf ",w[i]+k*pos[i]);
		}
		puts("");
	}
	return 0;
} 


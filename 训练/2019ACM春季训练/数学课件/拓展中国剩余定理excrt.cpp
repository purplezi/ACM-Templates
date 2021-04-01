//luogu P4777
//first pass luogu & niuke
#include<stdio.h>
#include<iostream>
using namespace std;
const int maxn=1e5+5;
typedef __int128 ll;
int n;
ll a[maxn],b[maxn];
int scan(ll &x){
    x=0;int sgn=1;
    char ch;
    while(ch=getchar()){
        if(ch==EOF)return EOF;
        else if(ch=='-')sgn=-sgn;
        else if(ch>='0'&&ch<='9'){
            x=x*10+(ch-'0');break;
        }
    }
    while((ch=getchar())>='0'&&ch<='9')x=x*10+(ch-'0');
    x*=sgn;return 1;
}
void _print(ll x){
    if(x>9)_print(x/10);
    putchar(x%10+'0');
}
void print(ll x){
    if(x<0){x=-x;putchar('-');}
    _print(x);
}
//a*x+b*y=gcd(a,b)
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(a==0&&b==0)return -1;
    if(b==0){x=1;y=0;return a;}
    ll d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
//china
ll excrt(){
    ll x,y,aa,bb,gcd;
    ll m=a[0],ans=b[0];//a[] divide b[] mod
    for(int i=1;i<n;i++){
        aa=a[i],bb=b[i];
        bb=((bb-ans)%aa+aa)%aa;
        gcd=exgcd(m,aa,x,y);
        if(bb%gcd)return -1;
        x=x*(bb/gcd)%(aa/gcd);
        x=(x+aa)%(aa/gcd);//change the sgn of x, because x maybe - change to +
        ans+=x*m;
        m=m/gcd*aa;
    }
    return ans;
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)scan(a[i]),scan(b[i]);
    print(excrt());
    return 0;
}

//extra method
//china x=ai(mod bi) a[] mod b[] divider 
ll excrt(){
    ll x,y,a0=a[0],b0=b[0],a1,b1,gcd;
    for(int i=1;i<n;i++){
        a1=((a[i]-a0)%b[i]+b[i])%b[i],b1=b[i];
        gcd=exgcd(b0,b1,x,y);
        if(a1%gcd)return -1;
        x=x*(a1/gcd)%b1;
        a0+=x*b0;
        b0*=b1/gcd;// b0 finally will be the lcm of all numbers
        a0=(a0+b0)%b0;//change the sgn of a0
    } 
    return a0;
}

//niuke https://ac.nowcoder.com/acm/contest/890/D
//second pass luogu & niuke
#include<stdio.h>
#include<iostream>
using namespace std;
const int maxn=1e2+5;
typedef __int128 ll;
int n;
ll a[maxn],b[maxn];
int scan(ll &x){
    x=0;
    int sgn=1;
    char ch;
    while(ch=getchar()){
        if(ch==EOF)return EOF;
        else if(ch=='-')sgn=-sgn;
        else if(ch>='0'&&ch<='9'){
            x=x*10+(ch-'0');break;
        }
    }
    while((ch=getchar())>='0'&&ch<='9')x=x*10+(ch-'0');
    x*=sgn;return 1;
}
void _print(ll x){
    if(x>9)_print(x/10);
    putchar(x%10+'0');
}
void print(ll x){
    if(x<0){x=-x;putchar('-');}
    _print(x);
}
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(a==0&&b==0)return -1;
    if(b==0){x=1;y=0;return a;}
    ll d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
ll excrt(){
    ll a1=b[0],n1=a[0],a2,n2,d,x,y,gcd;
    //if(a1==0)a1=a[0]; require positive number, so 0 is not correct
    for(int i=1;i<n;i++){
        a2=b[i];n2=a[i];
        d=a2-a1;
        gcd=exgcd(n1,n2,x,y);
        if(d%gcd)return -1;
        x=((x*d/gcd)%(n2/gcd)+(n2/gcd))%(n2/gcd);//k1=x*(d/gcd),k1=(k1%(n2/gcd)+(n2/gcd))%(n2/gcd)
        a1=x*n1+a1;//a1+k1*n1
        n1=n1*n2/gcd;//lcm(n1,n2)
    }
    return a1;
}
int main(){
    scanf("%d",&n);
    ll num;scan(num);
    for(int i=0;i<n;i++)scan(a[i]),scan(b[i]);
    ll ans=excrt();
    if(ans==-1)puts("he was definitely lying");
    else if(ans>num)puts("he was probably lying");
    else print(ans);
    return 0;
}



ll exgcd(ll a,ll b,ll &x,ll &y){
    //cout<<"hh"<<endl;
//  if(a==0&&b==0) return -1;
    ll t,res;
    if(b==0){
        x = 1;
        y = 0;
        return a;
    }
    res = exgcd(b,a%b,x,y);
    t = x;
    x = y;
    y=t - a/b*y;
    return res;
 
}
ll excrt(){
    //cout<<"hh"<<endl;
    int flag ;
    flag = 0;
    ll b1=b[0],a1=a[0],b2,a2,k1,k2,x0,gcd,c;
    ll t;
    for(int i=1;i<n;i++){
        b2=b[i],a2=a[i];
        c=b2-b1;
        gcd=exgcd(a1,a2,k1,k2);//解得：n1*k1+n2*k2=gcd(n1,n2)
        if(c%gcd){
            flag=1;
            //return -1;//无解
            break;
        }
        x0 = k1;
        k1=k1*c/gcd;//n1*x0+n2*(c/gcd*k2)=c  PS:k1/gcd*c错误！
        t=a2/gcd;
        k1=(k1%t+t)%t;//求n1*x0+n2*y=c的x0的最小解
        b1=a1*k1+b1;
        a1=a1*a2/gcd;
        //b1 = (b1%a1+a1)%a1;
   }
    //int res = (int )((N-a1)/n1+(a1==0?0:1));
  
    //int ans  = (N-b1)/a1 + (b1==0? 0:1);
    //int ans = 125;
    if(flag==1) b1 = -1;
    //cout<<"hh"<<endl;
    if(b1==0&&n>1) {
        b1 = a1;
    }
    //if(b1==0&&n==1) b1 =a[0];
    return b1;
 
}

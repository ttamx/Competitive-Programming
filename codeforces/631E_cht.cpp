#include<bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;
 
typedef long long ll;
typedef long double ld;

const int N=2e5+5;
 
int n;
ld sum,ans;
ld a[N],qs[N],dp[N];
 
const ld qr=123456789123456789;

struct line{
	mutable ld m,c,p;
	line(ld m=0,ld c=0,ld p=0):m(m),c(c),p(p){}
	bool operator<(const line&o)const{
		if(o.c==qr)return p<o.p;
		return m<o.m;
	}
};

struct convexhull:multiset<line>{
	ld inf=1.0/0.0;
	bool isect(iterator x,iterator y){
		if(y==end())return x->p=inf,false;
		if(x->m==y->m)x->p=x->c>=y->c?inf:-inf;
		else x->p=(x->c-y->c)/(y->m-x->m);
		return x->p>=y->p;
	}
	void add(ld m,ld c){
		auto x=insert(line(m,c,0)),y=x;
		while(isect(x,next(x)))erase(next(x));
		if(x!=begin()&&isect(--x,y))isect(x,erase(y));
		while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
	}
	ld get(ld x){
		if(empty())return -inf;
		auto l=*lower_bound(line(0,qr,x));
		return l.m*x+l.c;
	}
}cht;

 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+a[i];
    for(int i=1;i<=n;i++)sum+=a[i]*i;
    ans=sum;
    for(int i=1;i<=n;i++){
        ans=max(ans,cht.get(i)-qs[i]);
        cht.add(a[i],sum-a[i]*i+qs[i]);
    }
    cht.clear();
    for(int i=n;i>=1;i--){
        ans=max(ans,cht.get(i)-qs[i-1]);
        cht.add(a[i],sum-a[i]*i+qs[i-1]);
    }
    cout << (ll)ans;
}
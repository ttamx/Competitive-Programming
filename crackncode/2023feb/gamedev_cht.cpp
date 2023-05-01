#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int N=2e5+5;

struct line{
    mutable ll m,c;
    mutable ld p;
    bool operator<(const line &o)const{return m<o.m;}
    bool operator<(ll x)const{return p<x;}
};

struct convexhul:multiset<line,less<>>{
    ld inf=1e18;
    bool isect(iterator x,iterator y){
        if(y==end())return x->p=inf,false;
        if(x->m==y->m)x->p=x->c>=y->c?inf:-inf;
        else x->p=(x->c-y->c)/(y->m-x->m);
        return x->p>=y->p;
    }
    void add(ll m,ll c){
        auto x=insert({m,c,0});
        while(isect(x,next(x)))erase(next(x));
        auto y=x;
        if(x!=begin()&&isect(--x,y))isect(x,erase(y));
        while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
    }
    ll get(ll x){
        if(empty())return -1e18;
        auto l=lower_bound(x);
        return x*l->m+l->c;
    }
}cht;

int n;
ll a[N],dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)dp[i]=dp[i-1]+a[i];
    ll ans=0;
    for(int i=n;i>=1;i--){
        ans=max(ans,cht.get(i)+dp[i-1]);;
        cht.add(-a[i],a[i]*i-dp[i-1]);
    }
    cout << ans;
}
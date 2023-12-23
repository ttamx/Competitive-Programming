#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const ll inf=1e18;

int n;
ll h[N],w[N],qs[N],dp;

bool querymode=false;

struct line{
    ll m,c;
    mutable ll p;
    line(ll m,ll c):m(m),c(c),p(0){}
    line(ll p):m(0),c(0),p(p){}
    bool operator<(const line &o)const{
        return querymode?p<o.p:m>o.m;
    }
};

struct convexhulltrick:multiset<line>{
    ll div(ll a,ll b){
        return a/b-((a^b)<0&&a%b);
    }
    bool isect(iterator x,iterator y){
        if(y==end())return x->p=inf,false;
        if(x->m==y->m)x->p=x->c<=y->c?inf:-inf;
        else x->p=div(x->c-y->c,y->m-x->m);
        return x->p>=y->p;
    }
    void add(ll m,ll c){
        auto x=insert(line(m,c)),y=next(x);
        while(isect(x,y))y=erase(y);
        if((y=x)!=begin()&&isect(--x,y))isect(x,erase(y));
        while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
    }
    ll get(ll x){
        if(empty())return inf;
        querymode=true;
        auto l=lower_bound(line(x));
        querymode=false;
        return l->m*x+l->c;
    }
}cht;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> h[i];
    for(int i=1;i<=n;i++)cin >> w[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+w[i];
    cht.add(-2*h[1],-qs[1]+h[1]*h[1]);
    for(int i=2;i<=n;i++){
        dp=h[i]*h[i]+qs[i-1]+cht.get(h[i]);
        cht.add(-2*h[i],dp-qs[i]+h[i]*h[i]);
    }
    cout << dp;
}
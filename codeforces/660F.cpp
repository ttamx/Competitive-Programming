#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const ll inf=1e18;

int n;
ll a[N],qs[N],qs2[N];
ll ans;

bool querymode=false;

struct line{
    ll m,c;
    mutable ll p;
    line(ll p):p(p){}
    line(ll m,ll c):m(m),c(c){}
    bool operator<(const line &o)const{
        return querymode?p<o.p:m<o.m;
    }
};

struct linecontainer:multiset<line>{
    ll div(ll a,ll b){
        return a/b-((a^b)<0&&a%b);
    }
    bool isect(iterator x,iterator y){
        if(y==end())return x->p=inf,false;
        if(x->m==y->m)x->p=x->c>=y->c?inf:-inf;
        else x->p=div(x->c-y->c,y->m-x->m);
        return x->p>=y->p;
    }
    void add(ll m,ll c){
        auto y=insert(line(m,c)),x=y++;
        while(isect(x,y))y=erase(y);
        if((y=x)!=begin()&&isect(--x,y))isect(x,erase(y));
        while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
    }
    ll query(ll x){
        if(empty())return -inf;
        querymode=true;
        auto l=lower_bound(x);
        querymode=false;
        return l->m*x+l->c;
    }
}cht;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        qs[i]=qs[i-1]+a[i];
        qs2[i]=qs2[i-1]+i*a[i];
    }
    cht.add(0,0);
    for(int i=1;i<=n;i++){
        ans=max(ans,qs2[i]+cht.query(qs[i]));
        cht.add(-i,i*qs[i]-qs2[i]);
    }
    cout << ans << "\n";
}
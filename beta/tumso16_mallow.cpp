#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const int K=12;
const ll inf=1e18;

int n,k;
int w[N];
ll dp[K][N],qs[N],val[N];
bool querymode;

struct line{
    mutable ll m,c,p;
    line(ll p):m(0),c(-inf),p(p){}
    line(ll m,ll c):m(m),c(c),p(0){}
    bool operator<(const line &o)const{return querymode?p<o.p:m>o.m;}
};

struct convexhull:multiset<line>{
    ll div(ll a,ll b){return a/b-(a^b<0&&a%b);}
    bool isect(iterator x,iterator y){
        if(y==end())return x->p=inf,false;
        if(x->m==y->m)x->p=x->c<=y->c?inf:-inf;
        else x->p=div(x->c-y->c,y->m-x->m);
        return x->p>=y->p;
    }
    void add(ll m,ll c){
        auto y=insert(line(m,c)),x=y,z=next(y);
        while(isect(y,z))z=erase(z);
        if(x!=begin()&&isect(--x,y))isect(x,erase(y));
        while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
    }
    ll get(ll x){
        if(empty())return inf;
        querymode=true;
        auto l=lower_bound(line(x));
        querymode=false;
        return l->m*x+l->c;
    }
}cht[K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> w[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+w[i];
    for(int i=1;i<=n;i++)val[i]=val[i-1]+(1ll*i*w[i]);
    for(int i=1;i<=n;i++){
        dp[1][i]=dp[1][i-1]+(1ll*(i-1)*w[i]);
        cht[1].add(i+1,dp[1][i]-val[i]+qs[i]*(i+1));
    }
    for(int i=2;i<=k;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=val[j]+cht[i-1].get(-qs[j]);
            cht[i].add(j+1,dp[i][j]-val[j]+qs[j]*(j+1));
        }
    }
    cout << dp[k][n];
}
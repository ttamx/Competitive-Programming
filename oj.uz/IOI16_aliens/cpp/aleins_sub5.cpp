#include "aliens.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const int M=1e6+5;
const bool dbg=false;
const ll inf=1e18;

ll l[N],r[N];
ll overlap[N];
int mn[M];
stack<pair<int,int>> s;

bool querymode=false;

struct line{
    ll m,c;
    mutable ll p;
    line():m(0),c(-inf),p(0){}
    line(ll p):m(0),c(0),p(p){}
    line(ll m,ll c):m(m),c(c){}
    const bool operator<(const line &o)const{
        if(querymode)return p<o.p;
        return m<o.m;
    }
};

struct convexhulltrick:multiset<line>{
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
    ll get(ll x){
        if(empty())return -inf;
        querymode=true;
        auto l=lower_bound(line(x));
        querymode=false;
        return l->m*x+l->c;
    }
}cht;

long long take_photos(int n, int m, int k, vector<int> R, vector<int> C) {
    for(int i=0;i<m;i++)mn[i]=m;
    for(int i=0;i<n;i++){
        int x=R[i],y=C[i];
        int st=min(x,y),ed=max(x,y);
        mn[ed]=min(mn[ed],st);
    }
    for(int i=0;i<m;i++){
        if(mn[i]==m)continue;
        while(!s.empty()&&s.top().first>=mn[i])s.pop();
        s.emplace(mn[i],i);
    }
    n=s.size();
    for(int i=n;i>=1;i--){
        tie(l[i],r[i])=s.top();
        s.pop();
    }
    for(int i=1;i<n;i++){
        ll res=max(0ll,r[i]-l[i+1]+1);
        overlap[i]=res*res;
    }
    k=min(k,n);
    vector<vector<ll>> dp(k+1,vector<ll>(n+1,1e18));
    dp[0][0]=0;
    cht.add(l[1],-l[1]*l[1]);
    for(int i=1;i<=k;i++){
        dp[i][0]=0;
        for(int j=1;j<=n;j++){
            dp[i][j]=(r[j]+1)*(r[j]+1)-overlap[j]-cht.get(2*(r[j]+1));
        }
        for(int j=0;j<n;j++){
            cht.add(l[j+1],-l[j+1]*l[j+1]-dp[i][j]);
        }
    }
    ll ans=1e18;
    for(int i=0;i<=k;i++)ans=min(ans,dp[i][n]);
    return ans;
}

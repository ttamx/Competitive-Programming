#include "aliens.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const int M=1e6+5;
const bool dbg=false;
const ll inf=1e18;

int n;
ll l[N],r[N];
ll overlap[N];
int mn[M];
stack<pair<int,int>> s;

bool querymode=false;

struct line{
    ll m,c;
    int cnt;
    line():m(0),c(-inf){}
    line(ll m,ll c,int cnt):m(m),c(c),cnt(cnt){}
    ll get(ll x){
        return m*x+c;
    }
};

bool bad(line l1,line l2,line l3){
    return (l3.c-l1.c)*(l1.m-l2.m)<=(l2.c-l1.c)*(l1.m-l3.m);
}

pair<ll,int> calc(ll lambda){
    ll dp=0;
    int cnt=0;
    deque<line> dq;
    dq.emplace_back(line(l[1],-l[1]*l[1],0));
    for(int i=1;i<=n;i++){
        ll x=2*(r[i]+1);
        while(dq.size()>1&&dq[0].get(x)<dq[1].get(x))dq.pop_front();
        dp=(r[i]+1)*(r[i]+1)+lambda-overlap[i]-dq[0].get(x);
        cnt=dq[0].cnt+1;
        if(i==n)break;
        line ln(l[i+1],-dp-l[i+1]*l[i+1],cnt);
        while(dq.size()>1&&bad(dq[dq.size()-2],dq.back(),ln))dq.pop_back();
        dq.emplace_back(ln);
    }
    return make_pair(dp,cnt);
}

long long take_photos(int N, int m, int k, vector<int> R, vector<int> C) {
    n=N;
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
    ll lo=0,hi=1ll*m*m+1;
    ll ans=1;
    while(lo<hi){
        ll mid=(lo+hi)/2;
        auto [val,cnt]=calc(mid);
        if(cnt<=k)hi=mid,ans=val-mid*k;
        else lo=mid+1;
    }
    return ans;
}
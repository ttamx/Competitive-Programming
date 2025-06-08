#include <bits/stdc++.h>

using namespace std;

using ll = long long;

long long minimum_width(int B,int Z,vector<int> X){
    priority_queue<pair<int,ll>,vector<pair<int,ll>>,greater<pair<int,ll>>> pq;
    auto upd=[&](int l,int r,ll v){
        pq.emplace(l,v);
        if(r<Z)pq.emplace(r+1,~v);
    };
    ll area=0;
    for(int b=B;b>=0;b--){
        area+=ll(X[b])<<(2*b);
        if(area==0)continue;
        ll t=((area-1)>>(2*b+1))+1;
        auto calc=[&](ll h){
            return (t-1)/h+1;
        };
        for(ll h=1;(h<<b)<=Z;h++){
            ll w=calc(h);
            ll l=h,r=(Z>>b)+1;
            while(l<r){
                ll m=(l+r+1)/2;
                if(calc(m)==w)l=m;
                else r=m-1;
            }
            upd(h<<b,min(((l+1)<<b)-1,(ll)Z),w<<b);
            h=l;
        }
    }
    ll ans=0;
    int last=1<<B;
    multiset<ll> ms;
    ms.emplace(0LL);
    while(!pq.empty()){
        auto [p,v]=pq.top();
        pq.pop();
        if(last<p){
            ans+=(p-last)**ms.rbegin();
            last=p;
        }
        if(v>=0)ms.emplace(v);
        else ms.erase(ms.find(~v));
    }
    ans+=(Z-last+1)**ms.rbegin();
    return ans;
}
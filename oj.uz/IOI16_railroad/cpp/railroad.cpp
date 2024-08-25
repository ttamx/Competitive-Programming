#include "railroad.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll plan_roller_coaster(vector<int> s,vector<int> t){
    int n=s.size();
    vector<int> a;
    for(int i=0;i<n;i++){
        a.emplace_back(s[i]);
        a.emplace_back(t[i]);
    }
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    int m=a.size();
    for(auto &x:s)x=lower_bound(a.begin(),a.end(),x)-a.begin();
    for(auto &x:t)x=lower_bound(a.begin(),a.end(),x)-a.begin();
    vector<int> b(m),p(m);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        return p[u]=u==p[u]?u:fp(p[u]);
    };
    auto uni=[&](int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return false;
        return p[u]=v,true;
    };
    for(int i=0;i<n;i++){
        b[s[i]]++,b[t[i]]--;
        uni(s[i],t[i]);
    }
    ll ans=0;
    vector<pair<int,int>> e;
    for(int i=0;i<m-1;i++){
        b[i+1]+=b[i];
        ans+=1LL*max(0,b[i]-1)*(a[i+1]-a[i]);
        if(b[i]!=1)uni(i,i+1);
        else e.emplace_back(a[i+1]-a[i],i);
    }
    sort(e.begin(),e.end());
    for(auto [w,i]:e)if(uni(i,i+1))ans+=w;
    return ans;
}
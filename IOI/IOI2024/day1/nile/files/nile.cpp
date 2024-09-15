#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int INF=2e9;

vector<ll> calculate_costs(vector<int> w,vector<int> a,vector<int> b,vector<int> qr){
    int n=w.size();
    int q=qr.size();
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return w[i]<w[j];
    });
    auto work=[&](vector<int> &a){
        vector<int> res(n);
        for(int i=0;i<n;i++){
            res[i]=a[ord[i]];
        }
        swap(a,res);
    };
    work(w);
    work(a);
    work(b);
    vector<ll> ans(q);
    vector<int> ord2(q);
    iota(ord2.begin(),ord2.end(),0);
    sort(ord2.begin(),ord2.end(),[&](int i,int j){
        return qr[i]<qr[j];
    });
    vector<int> p(n);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        return p[u]=u==p[u]?u:fp(p[u]);
    };
    vector<int> sz(n,1),mn(n,INF);
    vector<array<int,2>> dp(n,{INF,INF});
    for(int i=0;i<n;i++){
        dp[i][i%2]=a[i]-b[i];
    }
    ll base=0;
    for(auto x:a){
        base+=x;
    }
    vector<pair<int,int>> event,event2;
    for(int i=0;i<n-1;i++){
        event.emplace_back(w[i+1]-w[i],i);
    }
    for(int i=1;i<n-1;i++){
        event2.emplace_back(w[i+1]-w[i-1],i);
    }
    sort(event.rbegin(),event.rend());
    sort(event2.rbegin(),event2.rend());
    auto calc=[&](int i){
        if(sz[i]%2==0){
            return 0;
        }
        return min(mn[i],dp[i][i%2]);
    };
    for(auto i:ord2){
        int d=qr[i];
        while(!event.empty()&&event.back().first<=d){
            int j=event.back().second;
            event.pop_back();
            int u=fp(j),v=fp(j+1);
            base-=calc(u);
            base-=calc(v);
            p[v]=u;
            mn[u]=min(mn[u],mn[v]);
            sz[u]+=sz[v];
            dp[u][0]=min(dp[u][0],dp[v][0]);
            dp[u][1]=min(dp[u][1],dp[v][1]);
            base+=calc(u);
        }
        while(!event2.empty()&&event2.back().first<=d){
            int j=event2.back().second;
            event2.pop_back();
            int u=fp(j);
            base-=calc(u);
            mn[u]=min(mn[u],a[j]-b[j]);
            base+=calc(u);
        }
        ans[i]=base;
    }
    return ans;
}

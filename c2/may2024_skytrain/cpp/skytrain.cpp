#include <bits/stdc++.h>
#include "skytrain.h"

using namespace std;

using ll = long long;

const int BIT=30;
const ll INF=LLONG_MAX/2;

ll min_total_cost(int N,int M,vector<int> A,vector<int> B,vector<int> W,ll K,int X,int Y){
    vector<vector<pair<int,int>>> adj(N);
    for(int i=0;i<M;i++){
        adj[A[i]].emplace_back(B[i],i);
        adj[B[i]].emplace_back(A[i],i);
    }
    ll ans=(1<<BIT)-1;
    auto upper=[&](int x){
        int res=0;
        bool bad=false;
        for(int i=0;i<BIT;i++){
            int a=x>>i&1;
            int b=ans>>i&1;
            if(a){
                if(b){
                    if(!bad)res|=1<<i;
                }else{
                    bad=true;
                    res=0;
                }
            }else if(b&&bad){
                bad=false;
                res|=1<<i;
            }
        }
        return (res>=x&&(ans|res)==ans)?res-x:x;
    };
    auto lower=[&](int x){
        int res=0;
        bool good=false;
        for(int i=BIT-1;i>=0;i--){
            int a=x>>i&1;
            int b=ans>>i&1;
            if(good){
                if(b)res|=1<<i;
            }else{
                if(a){
                    if(b)res|=1<<i;
                    else good=true;
                }
            }
        }
        return x-res;
    };
    auto calc=[&](int x){
        if((x|ans)==ans)return 0;
        return min(upper(x),lower(x));
    };
    for(int k=BIT-1;k>=0;k--){
        ans^=1<<k;
        vector<ll> dp(N,INF);
        using P = pair<ll,int>;
        priority_queue<P,vector<P>,greater<P>> pq;
        vector<ll> cost(M);
        for(int i=0;i<M;i++)cost[i]=calc(W[i]);
        pq.emplace(0,X);
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if(d>dp[u])continue;
            for(auto [v,i]:adj[u]){
                ll nd=d+cost[i];
                if(nd<dp[v]){
                    dp[v]=nd;
                    pq.emplace(nd,v);
                }
            }
        }
        if(dp[Y]>K)ans|=1<<k;
    }
    return ans;
}
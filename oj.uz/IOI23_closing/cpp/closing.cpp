#include "closing.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,int> p2;
typedef tuple<ll,ll,int> t3;

const int N=2e5+5;

int n;
vector<pair<int,int>> adj[N];
ll distx[N],disty[N],cost1[N],cost2[N];
bool used[N];

void dfs(int u,ll *dist,int p=-1){
    for(auto [v,w]:adj[u])if(v!=p){
        dist[v]=dist[u]+w;
        dfs(v,dist,u);
    }
}

int max_score(int N, int X, int Y, ll K, vector<int> U, vector<int> V, vector<int> W){
    n=N;
    for(int i=0;i<n-1;i++){
        int u=U[i],v=V[i],w=W[i];
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    distx[X]=disty[Y]=0;
    dfs(X,distx);
    dfs(Y,disty);
    for(int i=0;i<n;i++){
        cost1[i]=min(distx[i],disty[i]);
        cost2[i]=max(distx[i],disty[i])-cost1[i];
    }
    ll k=K;
    int ans=0;
    priority_queue<ll,vector<ll>,greater<ll>> pq;
    for(int i=0;i<n;i++)pq.emplace(cost1[i]);
    while(!pq.empty()&&pq.top()<=k){
        k-=pq.top();
        pq.pop();
        ans++;
    }
    k=K;
    int ans2=0;
    priority_queue<ll,vector<ll>,greater<ll>> pq1;
    priority_queue<p2,vector<p2>,greater<p2>> pq2,pq3;
    for(int i=0;i<n;i++){
        if(distx[i]+disty[i]==disty[X]){
            k-=cost1[i];
            ans2++;
            pq1.emplace(cost2[i]);
        }else if(cost1[i]<=cost2[i]){
            pq1.emplace(cost1[i]);
            pq1.emplace(cost2[i]);
        }else{
            pq2.emplace(cost1[i]+cost2[i],i);
            pq3.emplace(cost1[i],i);
        }
    }
    while(!pq1.empty()&&!pq2.empty()){
        ll val=pq1.top();
        pq1.pop();
        ll res1=val+(pq1.empty()?0:pq1.top());
        pq1.emplace(val);
        ll res2=pq2.top().first;
        if(pq1.size()>1&&res1<=res2){
            res1=pq1.top();
            if(res1>k)break;
            k-=res1;
            ans2++;
            pq1.pop();
        }else{
            if(res2>k)break;
            k-=res2;
            ans2+=2;
            used[pq2.top().second]=true;
            pq2.pop();
        }
    }
    while(!pq3.empty()){
        auto [v,i]=pq3.top();
        pq3.pop();
        if(!used[i])pq1.emplace(v);
    }
    while(!pq1.empty()&&pq1.top()<=k){
        k-=pq1.top();
        pq1.pop();
        ans2++;
    }
    for(int i=0;i<n;i++){
        adj[i].clear();
        used[i]=false;
    }
    if(k<0)return ans;
    return max(ans,ans2);
}
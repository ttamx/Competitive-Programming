#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll N=1e5+5;

ll n,m;
ll dist[N];
bool vis[N];
vector<tuple<ll,ll,ll>> adj[N];
priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;

ll go(ll st,ll w,ll f){
    bool red=(st/f)&1;
    ll res=st;
    ll cur=st;
    if(red){
        res+=f-(res%f);
    }
    ll rem=f-(res%f);
    if(rem>=w)return res+w;
    res+=rem;
    cur+=rem;
    w-=rem;
    ll dist=w;
    res+=dist;
    res+=f*((dist-1)/f)+f;
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(ll i=0;i<m;i++){
        ll u,v,w,f;
        cin >> u >> v >> w >> f;
        adj[u].emplace_back(v,w,f);
        adj[v].emplace_back(u,w,f);
    }
    for(ll i=1;i<=n;i++)dist[i]=1e18;
    pq.emplace(0,1);
    dist[1]=0;
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u]=true;
        for(auto [v,w,f]:adj[u]){
            ll res=go(d,w,f);
            if(res<dist[v]){
                dist[v]=res;
                pq.emplace(res,v);
            }
        }
    }
    cout << dist[n];
}
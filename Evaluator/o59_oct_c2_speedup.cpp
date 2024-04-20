#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,ll> p2;
typedef tuple<ll,int,int,int> t4;

const int N=8e4+5;

int n,m,l,q;
ll dp[N][10];
int a[N];
vector<p2> adj[N];
priority_queue<t4,vector<t4>,greater<t4>> pq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> l >> q;
    for(int i=0;i<m;++i){
        int u,v;
        ll w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
    }
    for(int i=1;i<=l;++i){
        int u;
        cin >> u;
        a[u]=i;
    }
    for(int i=0;i<=n;++i)for(int j=0;j<=q;++j)dp[i][j]=1e18;
    dp[1][0]=0;
    pq.emplace(0,1,0,0);
    while(!pq.empty()){
        auto [d,u,s,p]=pq.top();
        pq.pop();
        if(u==n){
            cout << d;
            break;
        }
        for(auto [v,w]:adj[u]){
            ll cost=d+(w>>s);
            if(cost>=dp[v][s])continue;
            pq.emplace(cost,v,s,p);
            dp[v][s]=cost;
        }
        if(s<q && a[u]>0 && a[u]!=p){
            pq.emplace(d,u,s+1,a[u]);
        }
    }
}

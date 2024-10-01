#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;

int n;
ll a[N];
vector<int> adj[N];
priority_queue<ll> pq[N];

void dfs(int u){
    for(auto v:adj[u]){
        dfs(v);
        if(pq[v].size()>pq[u].size()){
            swap(pq[u],pq[v]);
        }
        while(!pq[v].empty()){
            pq[u].emplace(pq[v].top());
            pq[v].pop();
        }
    }
    pq[u].emplace(a[u]);
    ll cur=3;
    while(true){
        ll val=cur*a[u];
        pq[u].emplace(val);
        ll pop=pq[u].top();
        pq[u].pop();
        if(val==pop)break;
        cur+=2;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=2;i<=n;i++){
        int p;
        cin >> p;
        adj[p].emplace_back(i);
    }
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    dfs(1);
    ll ans=0;
    while(!pq[1].empty()){
        ans+=pq[1].top();
        pq[1].pop();
    }
    cout << ans;
}
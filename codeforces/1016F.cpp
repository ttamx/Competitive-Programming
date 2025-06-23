#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    auto work=[&](int s){
        vector<ll> dist(n,INF);
        queue<int> q;
        dist[s]=0;
        q.emplace(s);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto [v,w]:adj[u]){
                if(dist[v]==INF){
                    dist[v]=dist[u]+w;
                    q.emplace(v);
                }
            }
        }
        return dist;
    };
    auto a=work(0);
    auto b=work(n-1);
    ll sp=a[n-1];
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return a[i]-b[i]<a[j]-b[j];
    });
    ll mx=0;
    vector<bool> f(n);
    multiset<ll> ms;
    for(auto u:ord){
        for(auto [v,w]:adj[u]){
            if(f[v]){
                ms.extract(a[v]);
            }
        }
        if(!ms.empty()){
            mx=max(mx,*ms.rbegin()+b[u]);
        }
        for(auto [v,w]:adj[u]){
            if(f[v]){
                ms.emplace(a[v]);
            }
        }
        f[u]=true;
        ms.emplace(a[u]);
    }
    while(q--){
        ll x;
        cin >> x;
        cout << min(sp,mx+x) << "\n";
    }
}
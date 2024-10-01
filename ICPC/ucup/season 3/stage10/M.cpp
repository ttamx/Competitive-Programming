#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<tuple<int,int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,c,w;
        cin >> u >> v >> c >> w;
        u--,v--,c--;
        adj[u].emplace_back(v,w,c);
        adj[v].emplace_back(u,w,c);
    }
    vector<bool> vis(n);
    using P = pair<int,int>;
    vector<priority_queue<P,vector<P>,greater<P>>> pq(m);
    vis[0]=true;
    for(auto [v,w,c]:adj[0]){
        pq[c].emplace(w,v);
    }
    for(int i=0;i<k;i++){
        int a,b;
        cin >> a >> b;
        a--;
        priority_queue<P,vector<P>,greater<P>> pq2;
        while(!pq[a].empty()){
            auto [d,u]=pq[a].top();
            if(d>b)break;
            pq[a].pop();
            pq2.emplace(d,u);
        }
        while(!pq2.empty()){
            auto [d,u]=pq2.top();
            pq2.pop();
            assert(d<=b);
            if(vis[u])continue;
            vis[u]=true;
            for(auto [v,w,c]:adj[u]){
                if(c==a&&w+d<=b){
                    pq2.emplace(d+w,v);
                }else{
                    pq[c].emplace(w,v);
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        cout << vis[i];
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}
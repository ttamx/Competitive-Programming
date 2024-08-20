#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    map<pair<int,int>,int> id;
    map<int,vector<pair<int,int>>> vx,vy;
    for(int i=0;i<n;i++){
        int x,y;
        cin >> x >> y;
        id[{x,y}]=i;
        vx[x].emplace_back(y,i);
        vy[y].emplace_back(x,i);
    }
    vector<vector<int>> adj(n);
    map<int,vector<pair<int,int>>> ver,hor;
    for(auto &[x,v]:vx){
        if(v.size()%2)return void(cout << "NO\n");
        sort(v.begin(),v.end());
        for(int i=0;i<v.size();i+=2){
            auto [uy,ui]=v[i];
            auto [vy,vi]=v[i+1];
            ver[uy].emplace_back(x,vy);
            adj[ui].emplace_back(vi);
            adj[vi].emplace_back(ui);
        }
    }
    for(auto &[y,v]:vy){
        if(v.size()%2)return void(cout << "NO\n");
        sort(v.begin(),v.end());
        for(int i=0;i<v.size();i+=2){
            auto [ux,ui]=v[i];
            auto [vx,vi]=v[i+1];
            hor[y].emplace_back(ux,vx);
            adj[ui].emplace_back(vi);
            adj[vi].emplace_back(ui);
        }
    }
    for(int i=0;i<n;i++)if(adj[i].size()!=2)return void(cout << "NO\n");
    vector<bool> vis(n);
    function<void(int)> dfs=[&](int u){
        if(vis[u])return;
        vis[u]=true;
        for(auto v:adj[u])dfs(v);
    };
    dfs(0);
    for(int i=0;i<n;i++)if(!vis[i])return void(cout << "NO\n");
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    multiset<int> ms;
    auto check=[&](int l,int r){
        return ms.upper_bound(l)==ms.lower_bound(r);
    };
    for(auto &[y,v]:hor){
        for(auto [x,t]:ver[y]){
            ms.emplace(x);
            pq.emplace(t,x);
        }
        for(auto [l,r]:v){
            if(!check(l,r))return void(cout << "NO\n");
        }
        while(!pq.empty()&&pq.top().first<=y){
            int x=pq.top().second;
            pq.pop();
            ms.erase(ms.find(x));
        }
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}
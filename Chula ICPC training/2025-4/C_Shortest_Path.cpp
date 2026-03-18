#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    set<tuple<int,int,int>> s;
    for(int i=0;i<k;i++){
        int x,y,z;
        cin >> x >> y >> z;
        x--,y--,z--;
        s.emplace(x,y,z);
    }
    queue<pair<int,int>> q;
    vector<vector<int>> pre(n,vector<int>(n,0));
    vector<vector<int>> dist(n,vector<int>(n,INF));
    auto push=[&](int p,int u,int v){
        if(dist[u][v]!=INF)return;
        dist[u][v]=dist[p][u]+1;
        pre[u][v]=p;
        q.emplace(u,v);
    };
    push(0,0,0);
    dist[0][0]=0;
    while(!q.empty()){
        auto [p,u]=q.front();
        q.pop();
        for(auto v:adj[u]){
            if(!s.count(make_tuple(p,u,v))){
                push(p,u,v);
            }
        }
    }
    int st=0;
    for(int i=0;i<n;i++){
        if(dist[i][n-1]<dist[st][n-1]){
            st=i;
        }
    }
    if(dist[st][n-1]==INF){
        cout << -1 << "\n";
        exit(0);
    }
    cout << dist[st][n-1] << "\n";
    vector<int> ans;
    for(int u=n-1;u!=0||st!=0;){
        ans.emplace_back(u);
        tie(u,st)={st,pre[st][u]};
    }
    ans.emplace_back(0);
    reverse(ans.begin(),ans.end());
    for(auto x:ans){
        cout << x+1 << " ";
    }
    cout << "\n";
}
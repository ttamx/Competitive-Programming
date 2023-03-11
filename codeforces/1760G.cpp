#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,a,b;
    cin >> n >> a >> b;
    vector<vector<pair<int,int>>> adj(n+1,vector<pair<int,int>>(0));
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    vector<int> dp1(n+1,0);
    map<int,bool> can;
    bool ans=false;
    function<void(int,int)> dfs1=[&](int u,int p){
        can[dp1[u]]=true;
        for(auto [v,w]:adj[u]){
            if(v==p||v==b)continue;
            dp1[v]=dp1[u]^w;
            dfs1(v,u);
        }
    };
    dfs1(a,-1);
    vector<int> dp2(n+1,0);
    function<void(int,int)> dfs2=[&](int u,int p){
        for(auto [v,w]:adj[u]){
            if(v==p)continue;
            dp2[v]=dp2[u]^w;
            if(can[dp2[v]])ans=true;
            dfs2(v,u);
        }
    };
    dfs2(b,-1);
    if(ans)cout << "YES\n";
    else cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}
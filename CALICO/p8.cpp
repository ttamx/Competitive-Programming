#include<bits/stdc++.h>

using namespace std;

using ll = long long;

using db = double;

void runcase(){
    int n,a,b;
    cin >> n >> a >> b;
    a--,b--;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        p--;
        adj[p].emplace_back(i);
    }
    vector<int> tin(n),tout(n),dep(n),par(n,-1);
    vector<db> dp(n);
    int timer=0;
    function<void(int)> dfs=[&](int u){
        tin[u]=++timer;
        for(auto v:adj[u]){
            dep[v]=dep[u]+1;
            par[v]=u;
            dfs(v);
            dp[u]+=dp[v];
        }
        if(!adj[u].empty()){
            dp[u]/=adj[u].size();
            dp[u]+=1;
        }
        tout[u]=timer;
    };
    dfs(0);
    if(dep[a]<dep[b]||!(tin[b]<=tin[a]&&tout[a]<=tout[b])){
        dp[a]=dp[b];
        for(auto v:adj[a]){
            dp[a]+=dp[v];
        }
        dp[a]/=(adj[a].size()+1);
        dp[a]+=1;
        for(int u=par[a];u!=-1;u=par[u]){
            dp[u]=0;
            for(auto v:adj[u]){
                dp[u]+=dp[v];
            }
            dp[u]/=adj[u].size();
            dp[u]+=1;
        }
        cout << dp[0] << "\n";
    }else{
        db l=dep[a]-dep[b]+1;
        db p=1.0/(adj[a].size()+1);
        db e=0;
        for(auto v:adj[a]){
            e+=dp[v]+1;
        }
        e/=(adj[a].size()+1);
        for(int u=a;u!=b;u=par[u]){
            for(auto v:adj[par[u]]){
                if(v!=u){
                    e+=dp[v];
                }
            }
            p/=adj[par[u]].size();
            e/=adj[par[u]].size();
            e+=1-p;
        }
        dp[b]=(e+p*l)/(1-p);
        for(int u=par[b];u!=-1;u=par[u]){
            dp[u]=0;
            for(auto v:adj[u]){
                dp[u]+=dp[v];
            }
            dp[u]/=adj[u].size();
            dp[u]+=1;
        }
        cout << dp[0] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}
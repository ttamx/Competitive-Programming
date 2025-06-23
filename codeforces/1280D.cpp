#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int INF=INT_MAX/2;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    for(auto &x:a){
        int y;
        cin >> y;
        x=y-x;
    }
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    using V = vector<pair<int,ll>>;
    vector<V> dp(n);
    auto merge=[&](const V &a,const V &b){
        V c(a.size()+b.size()-1,{-INF,0});
        for(int i=0;i<a.size();i++){
            for(int j=0;j<b.size();j++){
                c[i+j]=max(c[i+j],{a[i].first+b[j].first,a[i].second+b[j].second});
            }
        }
        return c;
    };
    function<void(int,int)> dfs=[&](int u,int p){
        V cur;
        cur.emplace_back(0,0);
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            cur=merge(cur,dp[v]);
        }
        dp[u].emplace_back(-INF,0);
        for(auto &[x,y]:cur){
            y+=a[u];
            dp[u].emplace_back(x+(y>0),0);
        }
        if(u==0)return;
        for(int i=0;i<cur.size();i++){
            dp[u][i]=max(dp[u][i],cur[i]);
        }
    };
    dfs(0,-1);
    cout << dp[0][m].first << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    int p,b;
    cin >> p >> b;
    vector<int> token(p),bonus(b);
    vector<bool> istoken(n),isbonus(n);
    for(auto &x:token){
        cin >> x;
        x--;
        istoken[x]=true;
    }
    for(auto &x:bonus){
        cin >> x;
        x--;
        isbonus[x]=true;
    }
    isbonus[0]=true;
    vector<pair<int,int>> edge(m);
    for(auto &[u,v]:edge){
        cin >> u >> v;
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(auto u:token){
        bool ok=(u==0);
        for(auto v:adj[u])ok|=(v==0);
        if(ok){
            cout << "YES\n";
            return;
        }
    }
    vector<int> vis(n);
    vector<int> dp(n);
    queue<int> q;
    q.push(0);
    vis[0]=true;
    vector<int> valid;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u]){
            if(vis[v]||!isbonus[v])continue;
            vis[v]=true;
            dp[u]=dp[v]+1;
            q.push(v);
        }
    }
    for(auto u:token){
        bool ok=vis[u];
        for(auto v:adj[u])ok|=vis[v];
        if(ok)valid.push_back(u);
    }
    if(valid.empty()){
        cout << "NO\n";
        return;
    }
    vector<bool> loop(n);
    for(auto [u,v]:edge)if(isbonus[u]&&isbonus[v])loop[u]=loop[v]=true;
    vector<int> looptoken;
    int cnt=0;
    vector<int> move(n);
    for(auto u:token){
        bool ok=loop[u];
        for(auto v:adj[u]){
            ok|=loop[v];
            if(move[u]==0&&isbonus[v]){
                move[u]++;
                cnt++;
            }
        }
        if(ok)looptoken.push_back(u);
    }
    bool canloop=!looptoken.empty();
    if(valid.size()==1&&looptoken.size()==1&&valid[0]==looptoken[0])canloop=false;
    if(canloop){
        cout << "YES\n";
        return;
    }
    for(auto u:valid){
        if(cnt-move[u]>=dp[u]){
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
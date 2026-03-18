#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n,m,s;
    cin >> n >> m >> s;
    s--;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x&=1;
    }
    vector<vector<int>> adj(n),adj2(n);;
    vector<int> c(n),par(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int uu=-1,vv=-1;
    vector<bool> vis(n);
    vector<int> col(n);
    function<int(int,int)> dfs=[&](int u,int p){
        par[u]=p;
        vis[u]=true;
        int s=0;
        for(auto v:adj[u])if(v!=p){
            if(!vis[v]){
                col[v]=col[u]^1;
                adj2[u].emplace_back(v);
                if(dfs(v,u)){
                    s=1;
                    c[v]++;
                    a[u]^=1;
                    a[v]^=1;
                }
                if(a[v]){
                    s=1;
                    c[v]++;
                    a[u]^=1;
                    a[v]^=1;
                }
            }else if(col[u]==col[v]){
                uu=u,vv=v;
            }
        }
        return s;
    };
    dfs(s,-1);
    for(int i=0;i<n;i++)if(!vis[i]&&a[i])return void(cout << "No\n");
    vector<int> ans;
    function<void(int)> dfs2=[&](int u){
        for(auto v:adj2[u]){
            while(c[v]>0){
                c[v]--;
                ans.emplace_back(v);
                dfs2(v);
                ans.emplace_back(u);
            }
        }
    };
    vector<int> path;
    if(a[s]){
        if(uu==-1)return void(cout << "No\n");
        vector<int> cycle,line;
        for(int u=vv;u!=uu;u=par[u])cycle.emplace_back(u);
        reverse(cycle.begin(),cycle.end());
        for(int u=uu;u!=s;u=par[u])line.emplace_back(u);
        reverse(line.begin(),line.end());
        assert(cycle.size()%2==0);
        for(int i=1;i<cycle.size();i+=2)c[cycle[i]]++;
        for(auto x:line)path.emplace_back(x);
        for(auto x:cycle)path.emplace_back(x);
        reverse(line.begin(),line.end());
        for(auto x:line)path.emplace_back(x);
        path.emplace_back(s);
        for(auto x:path)c[x]%=2;
    }
    dfs2(s);
    for(auto u:path){
        ans.emplace_back(u);
        dfs2(u);
    }
    assert(path.size()<=5*n);
    cout << "Yes\n";
    cout << ans.size() << "\n";
    for(auto x:ans){
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
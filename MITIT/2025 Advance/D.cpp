#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n;
    cin >> n;
    vector<int> x(n),y(n),dir(n);
    for(int i=0;i<n;i++){
        cin >> x[i] >> y[i];
        string s;
        cin >> s;
        dir[i]=s=="UD";
    }
    vector<vector<int>> adj(n*2),rev(n*2);
    auto link=[&](int u,int v){
        adj[u].emplace_back(v);
        rev[v].emplace_back(u);
    };
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(dir[i]==dir[j])continue;
            if(dir[i]){
                link(i+(y[i]<y[j]?n:0),j+(x[i]<x[j]?n:0));
            }else{
                link(i+(x[i]<x[j]?n:0),j+(y[i]<y[j]?n:0));
            }
        }
    }
    vector<bool> vis(2*n);
    vector<int> st,scc(2*n,-1);
    int cur_scc=-1;
    function<void(int)> dfs=[&](int u){
        if(vis[u])return;
        vis[u]=true;
        for(auto v:adj[u]){
            dfs(v);
        }
        st.emplace_back(u);
    };
    function<void(int)> dfs2=[&](int u){
        if(scc[u]!=-1)return;
        scc[u]=cur_scc;
        for(auto v:rev[u]){
            dfs2(v);
        }
    };
    for(int i=0;i<2*n;i++){
        dfs(i);
    }
    reverse(st.begin(),st.end());
    for(auto x:st){
        cur_scc=x;
        dfs2(x);
    }
    for(int i=0;i<n;i++){
        if(scc[i]==scc[i+n]){
            cout << "NO\n";
            cout << 0 << "\n";
            return;
        }
    }
    cout << "YES\n";
    cout << 1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}
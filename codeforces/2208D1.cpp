#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    vector<int> deg(n);
    for(int i=0;i<n;i++){
        if(a[i][i]=='0'){
            cout << "No\n";
            return;
        }
        for(int j=0;j<n;j++){
            if(i!=j&&a[i][j]=='1'){
                deg[j]++;
            }
        }
    }
    vector<int> ord;
    for(int i=0;i<n;i++){
        if(!deg[i]){
            ord.emplace_back(i);
        }
    }
    for(int i=0;i<ord.size();i++){
        int u=ord[i];
        for(int v=0;v<n;v++)if(u!=v&&a[u][v]=='1'){
            if(--deg[v]==0){
                ord.emplace_back(v);
            }
        }
    }
    if(ord.size()<n){
        cout << "No\n";
        return;
    }
    DSU dsu(n);
    vector<vector<int>> adj(n);
    vector<pair<int,int>> edges;
    for(int i=n-1;i>=0;i--){
        int u=ord[i];
        for(int j=i+1;j<n;j++){
            int v=ord[j];
            if(a[u][v]=='1'&&dsu.merge(u,v)){
                adj[u].emplace_back(v);
                edges.emplace_back(u,v);
            }
        }
    }
    if(edges.size()!=n-1){
        cout << "No\n";
        return;
    }
    for(int i=0;i<n;i++){
        string t(n,'0');
        queue<int> q;
        q.emplace(i);
        t[i]='1';
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto v:adj[u]){
                if(t[v]=='0'){
                    t[v]='1';
                    q.emplace(v);
                }
            }
        }
        if(a[i]!=t){
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
    for(auto [u,v]:edges){
        cout << u+1 << " " << v+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
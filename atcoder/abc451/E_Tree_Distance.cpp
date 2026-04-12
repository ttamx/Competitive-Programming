#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> a(n,vector<int>(n));
    vector<tuple<int,int,int>> b;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            cin >> a[i][j];
            a[j][i]=a[i][j];
            b.emplace_back(a[i][j],i,j);
        }
    }
    DSU dsu(n);
    vector<vector<int>> adj(n);
    sort(b.begin(),b.end());
    for(auto [x,u,v]:b){
        if(dsu.merge(u,v)){
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
            continue;
        }
        bool ok=false;
        for(auto k:adj[u]){
            int d=a[u][k]+a[k][v];
            if(d<x){
                ok=false;
                break;
            }
            if(d==x)ok=true;
        }
        if(!ok){
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
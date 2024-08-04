#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<vector<ll>> a(n,vector<ll>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            cin >> a[i][j];
            a[j][i]=a[i][j];
        }
    }
    auto dist=[&](int u,int v){
        ll d=a[u][u]+a[v][v]-2*a[u][v];
        assert(d%n==0);
        return d/n;
    };
    DSU dsu(n);
    vector<tuple<ll,int,int>> edges;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            edges.emplace_back(dist(i,j),i,j);
        }
    }
    sort(edges.begin(),edges.end());
    for(auto [w,u,v]:edges){
        if(dsu.merge(u,v)){
            cout << u+1 << " " << v+1 << " " << w << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
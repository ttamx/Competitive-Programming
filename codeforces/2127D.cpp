#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> edges(m);
    vector<vector<int>> adj(n);
    for(auto &[u,v]:edges){
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    if(m!=n-1){
        cout << 0 << "\n";
        return;
    }
    if(n==2){
        cout << 2 << "\n";
        return;
    }
    int cnt=0;
    vector<int> num(n);
    for(int i=0;i<n;i++){
        if(adj[i].size()==1){
            num[adj[i][0]]++;
        }else{
            cnt++;
        }
    }
    if(cnt==1){
        for(int i=0;i<n;i++){
            if(adj[i].size()>1){
                cout << comb.fac(num[i])*2 << "\n";
                return;
            }
        }
        assert(false);
    }
    vector<int> deg(n);
    for(auto [u,v]:edges){
        if(adj[u].size()>1&&adj[v].size()>1){
            deg[u]++;
            deg[v]++;
        }
    }
    cnt=0;
    for(int i=0;i<n;i++){
        if(deg[i]==1){
            cnt++;
            if(cnt>2){
                cout << 0 << "\n";
                return;
            }
        }else if(deg[i]>2){
            cout << 0 << "\n";
            return;
        }
    }
    assert(cnt==2);
    mint ans=4;
    for(int i=0;i<n;i++){
        ans*=comb.fac(num[i]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
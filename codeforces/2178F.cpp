#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int tot=n;
    vector<mint> a;
    function<int(int,int)> dfs=[&](int u,int p){
        int s=1;
        for(auto v:adj[u]){
            if(v==p)continue;
            s+=dfs(v,u);
        }
        if(s%2==0&&u!=0){
            a.emplace_back(s);
            tot-=s;
            s=0;
        }
        return s;
    };
    dfs(0,-1);
    if(a.empty()){
        cout << 1 << "\n";
        return;
    }
    mint ways=1;
    for(auto x:a)ways*=x*x;
    for(int i=1;i<a.size();i++)ways*=i;
    mint ans=0;
    for(auto x:a)ans+=ways/x;
    cout << ans*tot << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
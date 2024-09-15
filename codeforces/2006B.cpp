#include "template.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"

void runcase(){
    int n;
    ll w;
    cin >> n >> w;
    Graph g(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        g.add_edge(i,p-1);
    }
    HLD hld(g);
    vector<vector<int>> ids(n);
    vector<int> cnt(n);
    for(int i=0;i<n;i++){
        int x=hld.lca(i,(i+1)%n);
        for(int u=i;u!=x;u=hld.par[u]){
            ids[u].emplace_back(i);
            cnt[i]++;
        }
        for(int u=(i+1)%n;u!=x;u=hld.par[u]){
            ids[u].emplace_back(i);
            cnt[i]++;
        }
    }
    vector<ll> val(n);
    ll ans=n*w;
    ll unknown=n;
    ll lazy=0;
    for(int i=0;i<n-1;i++){
        int x;
        ll y;
        cin >> x >> y;
        x--;
        ans-=(unknown-2)*y;
        lazy+=y;
        for(auto j:ids[x]){
            cnt[j]--;
            val[j]+=y;
            if(cnt[j]==0){
                unknown--;
                ans-=w-lazy;
            }
        }
        cout << ans << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
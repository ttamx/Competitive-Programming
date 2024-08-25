#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/max.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n),add(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[v].emplace_back(u);
        add[u].emplace_back(v);
    }
    vector<int> dp(n);
    for(int i=1;i<n;i++){
        dp[i]=dp[i-1];
        for(auto j:adj[i]){
            dp[i]=min(dp[i],dp[j]);
        }
        dp[i]++;
    }
    SegmentTree<MaxMonoid<int>> seg(n);
    for(int i=0;i<n-1;i++){
        cout << (seg.query(i+1,n-1)>i?0:1);
        for(auto j:add[i]){
            seg.update(j,j-dp[i]-1);
        }
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
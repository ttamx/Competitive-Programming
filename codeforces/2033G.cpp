#include "template.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/max.hpp"

void runcase(){
    int n;
    cin >> n;
    auto g=read_tree(n);
    HLD hld(g);
    vector<pair<int,int>> dp(n);
    SegmentTree<MaxMonoid<int>> seg(n);
    function<void(int)> dfs=[&](int u){
        for(int v:g[u]){
            if(v==hld.par[u])continue;
            dfs(v);
            dp[u].second=max(dp[u].second,dp[v].first+1);
            if(dp[u].second>dp[u].first){
                swap(dp[u].first,dp[u].second);
            }
        }
        int h=hld.hv[u];
        if(h!=-1&&dp[u].first==dp[h].first+1){
            seg.modify(hld.tin[u],dp[u].second-hld.dep[u]);
        }else{
            seg.modify(hld.tin[u],dp[u].first-hld.dep[u]);
        }
    };
    dfs(0);
    int q;
    cin >> q;
    while(q--){
        int u,k;
        cin >> u >> k;
        u--;
        int d=hld.dep[u];
        int ans=dp[u].first-d;
        while(u!=-1&&k>=hld.dep[u]-hld.dep[hld.head[u]]){
            if(u!=hld.head[u]){
                k-=hld.dep[u]-hld.dep[hld.head[u]];
                ans=max(ans,seg.query(hld.tin[hld.head[u]],hld.tin[u]-1));
                u=hld.head[u];
            }
            if(k>0){
                k--;
                int p=hld.par[u];
                if(p!=-1){
                    if(dp[p].first==dp[u].first+1){
                        ans=max(ans,dp[p].second-hld.dep[p]);
                    }else{
                        ans=max(ans,dp[p].first-hld.dep[p]);
                    }
                }
                u=p;
            }else{
                break;
            }
        }
        if(k>0&&u>0){
            ans=max(ans,seg.query(max(0,hld.tin[u]-k),hld.tin[u]-1));
        }
        cout << ans+d << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
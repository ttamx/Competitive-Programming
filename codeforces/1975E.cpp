#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/min-count-add.hpp"
#include "group/monoid-action/max-add.hpp"

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> col(n);
    vector<vector<int>> adj(n);
    for(auto &x:col)cin >> x;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> par(n,-1),disc(n),l(n,n),r(n,-1),bfs{0};
    for(int i=0;i<n;i++){
        int u=bfs[i];
        disc[u]=i;
        if(par[u]!=-1){
            l[par[u]]=min(l[par[u]],i);
            r[par[u]]=i;
        }
        for(auto v:adj[u])if(v!=par[u]){
            par[v]=u;
            bfs.emplace_back(v);
        }
    }
    LazySegmentTree<MinCountAddAction<int>> smn(n);
    LazySegmentTree<MaxAddAction<int>> smx(n);
    int cnt=0;
    for(int i=0;i<n;i++){
        int u=bfs[i];
        int res=0;
        for(auto v:adj[u])res+=col[v];
        smn.modify(i,pair<int,int>(res+(col[u]?0:INF),1));
        smx.modify(i,res+(col[u]?0:-INF));
        cnt+=col[u];
    }
    while(q--){
        int u;
        cin >> u;
        u--;
        if(col[u]){
            cnt--;
            smn.update(disc[u],disc[u],INF);
            smx.update(disc[u],disc[u],-INF);
            if(par[u]!=-1){
                int i=disc[par[u]];
                smn.update(i,i,-1);
                smx.update(i,i,-1);
            }
            if(l[u]<=r[u]){
                smn.update(l[u],r[u],-1);
                smx.update(l[u],r[u],-1);
            }
        }else{
            cnt++;
            smn.update(disc[u],disc[u],-INF);
            smx.update(disc[u],disc[u],INF);
            if(par[u]!=-1){
                int i=disc[par[u]];
                smn.update(i,i,1);
                smx.update(i,i,1);
            }
            if(l[u]<=r[u]){
                smn.update(l[u],r[u],1);
                smx.update(l[u],r[u],1);
            }
        }
        col[u]^=1;
        if(cnt==0)cout << "No\n";
        else if(cnt==1)cout << "Yes\n";
        else{
            auto [v,f]=smn.query(0,n-1);
            auto mx=smx.query(0,n-1);
            cout << (v==1&&f==2&&mx<=2?"Yes":"No") << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
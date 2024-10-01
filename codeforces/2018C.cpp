#include "template.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"

void runcase(){
    int n;
    cin >> n;
    auto g=read_tree(n);
    HLD hld(g);
    vector<vector<int>> nodes(n);
    for(int i=1;i<n;i++){
        nodes[hld.dep[i]].emplace_back(i);
    }
    int ans=n-1;
    for(int d=1;d<n;d++){
        auto &a=nodes[d];
        if(a.empty())continue;
        a.emplace_back(0);
        sort(a.begin(),a.end(),[&](int i,int j){return hld.tin[i]<hld.tin[j];});
        int res=0;
        stack<int> s;
        for(auto u:a){
            int v=-1;
            while(!s.empty()&&!hld.is_ancestor(s.top(),u)){
                v=s.top();
                s.pop();
            }
            if(v!=-1){
                int x=hld.lca(u,v);
                if(s.empty()){
                    res+=hld.dep[v]-hld.dep[x];
                }
                s.emplace(x);
            }
            if(!s.empty()){
                res+=hld.dep[u]-hld.dep[s.top()];
            }
            s.emplace(u);
        }
        ans=min(ans,n-res-1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
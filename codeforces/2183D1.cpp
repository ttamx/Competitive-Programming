#include "template.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"

void runcase(){
    int n;
    cin >> n;
    auto g=read_tree(n);
    HLD hld(g);
    int ans=1+g[0].size();
    vector<int> cnt(n);
    for(int i=0;i<n;i++)ans=max(ans,++cnt[hld.dep[i]]);
    for(int i=1;i<n;i++)ans=max(ans,(int)g[i].size());
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
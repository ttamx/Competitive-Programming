#include "template.hpp"
#include "data-structure/cartesian-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    CartesianTree<int,false> ct(a);
    vector<vector<pair<int,int>>> event(n+1);
    auto add=[&](int l,int r,int v){
        if(v<0)return;
        event[r].emplace_back(v,+1);
        if(l>0)event[l-1].emplace_back(v,-1);
    };
    function<void(int,int,int)> dfs=[&](int l,int r,int u){
        if(l>r)return;
        dfs(l,u-1,ct.lch[u]);
        dfs(u+1,r,ct.rch[u]);
        if(u-l<r-u){
            for(int i=l;i<=u;i++){
                add(u,r,a[u]-a[i]);
            }
        }else{
            for(int i=u;i<=r;i++){
                add(l,u,a[u]-a[i]);
            }
        }
    };
    dfs(0,n-1,ct.root);
    vector<int> cnt(n+1);
    ll ans=0;
    for(int i=0;i<n;i++){
        cnt[a[i]]++;
        for(auto [x,c]:event[i]){
            ans+=cnt[x]*c;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
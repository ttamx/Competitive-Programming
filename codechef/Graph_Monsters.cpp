#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<ll> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    vector<tuple<int,int,int>> edges(m);
    for(auto &[w,u,v]:edges){
        cin >> u >> v;
        u--,v--;
        w=max(a[u],a[v]);
    }
    sort(edges.begin(),edges.end());
    ll l=0,r=0;
    for(auto x:a){
        r+=x;
    }
    auto check=[&](ll mid)->bool {
        auto sum=b;
        vector<bool> dp(n,true);
        DSU dsu(n);
        for(auto [w,u,v]:edges){
            if(dsu.same(u,v))continue;
            u=dsu.find(u),v=dsu.find(v);
            bool ok=false;
            if(dp[u]&&sum[u]+mid>=w)ok=true;
            if(dp[v]&&sum[v]+mid>=w)ok=true;
            sum[u]+=sum[v];
            dp[u]=ok;
            dsu.merge(u,v);
        }
        return dp[dsu.find(0)];
    };
    while(l<r){
        ll m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    ll ans=l;
    for(auto x:b){
        ans+=x;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
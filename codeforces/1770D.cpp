#include "template.hpp"
#include "data-structure/dsu.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    DSU dsu(n);
    vector<pair<int,int>> a(n);
    for(int i=0;i<n;i++)cin >> a[i].first;
    for(int i=0;i<n;i++)cin >> a[i].second;
    vector<int> cnt(n);
    for(auto &[u,v]:a)dsu.merge(--u,--v);
    for(auto [u,v]:a)cnt[dsu.find(u)]++;
    for(int i=0;i<n;i++)if(i==dsu.find(i)&&cnt[i]!=dsu.size(i))return void(cout << 0 << "\n");
    mint ans=1;
    vector<bool> bad(n);
    for(auto [u,v]:a)if(u==v)ans*=n,bad[dsu.find(u)]=true;
    for(int i=0;i<n;i++)if(!bad[i]&&i==dsu.find(i))ans*=2;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
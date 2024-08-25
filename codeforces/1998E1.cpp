#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<pair<int,int>> e;
    for(int i=0;i+1<n;i++)e.emplace_back(max(a[i],a[i+1]),i);
    DSU dsu(n);
    vector<ll> sum(n),cnt(n);
    for(int i=0;i<n;i++){
        sum[i]=a[i];
        cnt[i]=1;
    }
    sort(e.begin(),e.end());
    for(auto [val,i]:e){
        int u=i,v=i+1;
        ll su=sum[dsu.find(u)];
        ll sv=sum[dsu.find(v)];
        ll res=0;
        if(su>=val)res+=cnt[dsu.find(u)];
        if(sv>=val)res+=cnt[dsu.find(v)];
        dsu.merge(u,v);
        sum[dsu.find(u)]=su+sv;
        cnt[dsu.find(u)]=res;
    }
    cout << cnt[dsu.find(0)] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

using i128 = __int128_t;

const ll LIM=1e18;

void runcase(){
    int n,k;
    cin >> n >> k;
    i128 tar=1;
    for(int i=1;i<k;i++)tar*=10;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    Fenwick<ll> f(n);
    auto b=a;
    sort(b.begin(),b.end());
    ll ans=0;
    for(int i=0;i<n;i++){
        ll x=a[i];
        if(x>=tar*10)continue;
        int l=lower_bound(b.begin(),b.end(),tar-x)-b.begin();
        int r=upper_bound(b.begin(),b.end(),tar*10-x-1)-b.begin()-1;
        if(l<=r)ans+=f.query(l,r)*(n-i);
        f.update(lower_bound(b.begin(),b.end(),x)-b.begin(),i+1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
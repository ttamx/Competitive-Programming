#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    Fenwick<ll> f(m),f2(m);
    ll ans=0;
    f.update(0,1);
    ll sum=0;
    for(int i=0;i<n;i++){
        ll x;
        cin >> x;
        sum+=x;
        sum%=m;
        ans+=sum*f.query(sum)-f2.query(sum);
        ans+=(sum+m)*f.query(sum+1,m-1)-f2.query(sum+1,m-1);
        f.update(sum,1);
        f2.update(sum,sum);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
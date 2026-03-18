#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    auto b=a;
    sort(b.begin(),b.end());
    for(auto &x:a)x=lower_bound(b.begin(),b.end(),x)-b.begin();
    Fenwick<int> fcnt(n);
    Fenwick<ll> fsum(n);
    for(int i=0;i<n;i++){
        fcnt.update(a[i],1);
        fsum.update(a[i],b[a[i]]);
        if(i<2)continue;
        auto calc=[&](int k){
            int xl=fcnt.find(k-1);
            int xr=fcnt.find(k+1);
            ll vl=b[xl]*k-fsum.query(xl);
            ll vr=fsum.query(xr,n-1)-b[xr]*(i-k);
            return max(vl,vr);
        };
        int l=0,r=i;
        while(l<r){
            int m=(l+r)/2;
            if(calc(m+1)<calc(m))l=m+1;
            else r=m;
        }
        cout << mint(calc(l))/mint(i-1) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
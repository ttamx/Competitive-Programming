#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<tuple<int,int,int>> qr(q);
    for(auto &[w,l,r]:qr){
        cin >> l >> r >> w;
        l--,r--;
    }
    sort(qr.begin(),qr.end());
    ll ans=0;
    DSU dsu(n);
    for(auto [w,l,r]:qr){
        for(int i=l;i<=r;i++){
            i=dsu.find(i);
            ans+=w;
            if(i<r){
                dsu.merge(i+1,i);
            }
        }
    }
    if(dsu.size(0)<n){
        cout << -1 << "\n";
    }else{
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
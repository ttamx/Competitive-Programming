#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "data-structure/fenwick-tree.hpp"

using mint = mint107;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<Fenwick<mint>> f1(n+1,Fenwick<mint>(n+1)),f2(n+1,Fenwick<mint>(n+1));
    f1[0].update(0,+1);
    f2[0].update(0,+1);
    for(auto x:a){
        vector<tuple<int,int,mint>> to_upd;
        for(int i=0;i<=n;i++){
            to_upd.emplace_back(i,x,f1[i].query(x));
        }
        for(int i=x+1;i<=n;i++){
            to_upd.emplace_back(x,i,f2[i].query(x));
        }
        for(auto [x,y,v]:to_upd){
            f1[x].update(y,v);
            f2[y].update(x,v);
        }
    }
    mint ans=0;
    for(int i=0;i<=n;i++){
        ans+=f1[i].query(n);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
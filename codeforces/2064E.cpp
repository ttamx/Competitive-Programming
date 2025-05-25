#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "data-structure/fenwick-tree.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/max.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> p(n),c(n);
    for(auto &x:p){
        cin >> x;
    }
    for(auto &x:c){
        cin >> x;
        x--;
    }
    reverse(p.begin(),p.end());
    reverse(c.begin(),c.end());
    vector<vector<int>> pos(n);
    for(int i=0;i<n;i++){
        pos[c[i]].emplace_back(i);
    }
    mint ans=1;
    Fenwick<int> f(n);
    SegmentTree<MaxMonoid<int>> seg(p);
    for(int col=0;col<n;col++){
        for(auto i:pos[col]){
            seg.modify(i,0);
            f.update(i,+1);
        }
        auto ord=pos[col];
        sort(ord.begin(),ord.end(),[&](int i,int j){
            return p[i]<p[j];
        });
        for(auto i:ord){
            int l=seg.findlast(0,i,[&](int x){return x>p[i];})+1;
            int r=seg.findfirst(i,n-1,[&](int x){return x>p[i];})-1;
            ans*=f.query(l,r);
            f.update(i,-1);
        }
        for(auto i:pos[col]){
            seg.modify(i,p[i]);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    map<int,vector<int>> pos;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        pos[x].emplace_back(i);
    }
    ll ans=0;
    Fenwick<int> f(n);
    int tot=0;
    for(auto &[_,v]:pos){
        for(auto i:v){
            int x=f.query(i);
            ans+=min(x,tot-x);
        }
        for(auto i:v){
            f.update(i,+1);
            tot++;
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
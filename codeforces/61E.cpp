#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<pair<int,int>> a;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a.emplace_back(x,i);
    }
    sort(a.rbegin(),a.rend());
    Fenwick<int> f1(n),f2(n);
    for(int i=0;i<n;i++){
        f1.update(i,+1);
    }
    ll ans=0;
    for(auto [_,i]:a){
        f1.update(i,-1);
        ans+=1LL*f1.query(i,n-1)*f2.query(0,i);
        f2.update(i,+1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
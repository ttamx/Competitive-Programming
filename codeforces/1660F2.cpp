#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<Fenwick<int>> f(3,Fenwick<int>(2*n+1));
    int cur=n;
    ll ans=0;
    for(int i=0;i<n;i++){
        f[(cur%3+3)%3].update(cur,+1);
        cur+=(s[i]=='-'?1:-1);
        ans+=f[(cur%3+3)%3].query(cur);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
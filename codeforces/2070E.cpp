#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    Fenwick<int> f(4*n+2);
    vector<int> cnt(4*n+2);
    ll ans=0;
    int cur=3*n;
    f.update(3*n,1);
    cnt[3*n]++;
    for(auto x:s){
        cur+=(x=='0'?1:-3);
        ans+=f.query(cur-2);
        ans+=cnt[cur+1];
        f.update(cur,1);
        cnt[cur]++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
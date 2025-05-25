#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    ll ans=0;
    Fenwick<int> f(n);
    vector<int> pos(n);
    for(int i=0;i<n;i++){
        pos[a[i]]=i;
        f.update(i,+1);
    }
    vector<int> cnt(n);
    for(int i=n-1;i>=0;i--){
        int p=f.query(pos[i])-1;
        cnt[p]++;
        cnt[i]--;
        f.update(pos[i],-1);
    }
    ll cur=0;
    for(int i=0;i<n;i++){
        ans+=cur*i;
        cur+=cnt[i];
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        b[--a[i]]=i;
    }
    Fenwick<int> f(n);
    ll ans=0;
    for(int i=n-1;i>=0;i--){
        ans+=min(f.query(b[i]),f.query(b[i],n-1));
        f.update(b[i],+1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),pre(n),suf(n);
    for(auto &x:a)cin >> x,x--;
    {
        Fenwick<int> f(n);
        for(int i=0;i<n;i++){
            f.update(a[i],+1);
            pre[i]=f.query(a[i]);
        }
    }
    {
        Fenwick<int> f(n);
        for(int i=n-1;i>=0;i--){
            f.update(a[i],+1);
            suf[i]=f.query(a[i]);
        }
    }
    ll ans=0;
    for(int i=0;i<n;i++)ans+=1LL*pre[i]*suf[i];
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
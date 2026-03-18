#include "template.hpp"
#include "data-structure/cartesian-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> b(n-1);
    for(int i=0;i+1<n;i++)b[i]=abs(a[i]-a[i+1]);
    CartesianTree<int,true> ct(b);
    vector<ll> ans(n);
    for(int i=0;i<n-1;i++){
        auto [l,r]=ct.range[i];
        ans[b[i]]+=1LL*(i-l+1)*(r-i+1);
    }
    for(int i=n-2;i>=1;i--)ans[i]+=ans[i+1];
    for(int i=1;i<n;i++)cout << ans[i] << " \n"[i==n-1];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
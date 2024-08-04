#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/min.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    SegmentTree<MinMonoid<int>> seg(a);
    vector<ll> ans(n);
    auto add=[&](int l,int r,ll v){
        if(l>r)return;
        ans[l]+=v;
        if(r+1<n)ans[r+1]-=v;
    };
    for(int i=0;i<n;i++){
        int l=seg.findlast(0,i-1,[&](int x){return x<a[i];});
        int l2=seg.findlast(0,l-1,[&](int x){return x<a[i];});
        int r=seg.findfirst(i+1,n-1,[&](int x){return x<a[i];});
        int r2=seg.findfirst(r+1,n-1,[&](int x){return x<a[i];});
        if(i>0){
            if(l==-1){
                add(0,i-1,a[i]*(i-l-1)*(r-i));
            }else{
                add(l+1,i-1,a[i]*(i-l-1)*(r-i));
                add(0,l-1,a[i]*(i-l)*(r-i));
                add(l,l,a[i]*(i-l2-1)*(r-i));
            }
        }
        if(i<n-1){
            if(r==n){
                add(i+1,n-1,a[i]*(i-l)*(r-i-1));
            }else{
                add(i+1,r-1,a[i]*(i-l)*(r-i-1));
                add(r+1,n-1,a[i]*(i-l)*(r-i));
                add(r,r,a[i]*(i-l)*(r2-i-1));
            }
        }
    }
    for(int i=0;i+1<n;i++)ans[i+1]+=ans[i];
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/min.hpp"
#include "group/monoid/max.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    SegmentTree<MinMonoid<int>> smn(a);
    SegmentTree<MaxMonoid<int>> smx(a);
    set<int> s;
    for(int i=1;i<n;i++)if(a[i]<a[i-1])s.emplace(i);
    auto work=[&](){
        if(s.empty())return void(cout << -1 << " " << -1 << "\n");
        int mn=smn.query(*s.begin(),n-1);
        int mx=smx.query(0,*s.rbegin()-1);
        int l=smx.findfirst(0,n-1,[&](int x){return x>mn;});
        int r=smn.findlast(0,n-1,[&](int x){return x<mx;});
        cout << l+1 << " " << r+1 << "\n";
    };
    work();
    int q;
    cin >> q;
    while(q--){
        int i,x;
        cin >> i >> x;
        i--;
        s.erase(i);
        s.erase(i+1);
        a[i]=x;
        if(i>0&&a[i]<a[i-1])s.emplace(i);
        if(i+1<n&&a[i+1]<a[i])s.emplace(i+1);
        smn.modify(i,x);
        smx.modify(i,x);
        work();
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
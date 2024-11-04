#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/monoid-base.hpp"

using mint = mint107;

struct Info{
    ll val;
    mint ways;
    Info():val(LINF),ways(0LL){}
    Info(ll _val,mint _ways):val(_val),ways(_ways){}
};

Info combine(Info lhs,Info rhs){
    if(lhs.val<rhs.val)return lhs;
    if(lhs.val>rhs.val)return rhs;
    return Info(lhs.val,lhs.ways+rhs.ways);
}

Info identity(){
    return Info();
}

using Monoid = MonoidBase<Info,combine,identity>;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(m);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    SegmentTree<Monoid> seg(n+1,Info());
    seg.modify(0,Info(0,1));
    for(int i=0;i<m;i++){
        ll sum=0;
        for(int l=0,r=0;r<n;r++){
            sum+=a[r];
            while(sum>b[i]){
                sum-=a[l];
                l++;
            }
            if(l<=r){
                Info tmp=seg.query(l,r);
                tmp.val+=m-i-1;
                seg.update(r+1,tmp);
            }
        }
    }
    Info ans=seg.query(n,n);
    if(ans.val<LINF){
        cout << ans.val << " " << ans.ways << "\n";
    }else{
        cout << -1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"

struct Monoid{
    using P = pair<int,int>;
    using value_type = P;
    static P op(const P &x,const P &y){return min(x,y);}
    static P unit(){return P(INF,-1);}
};

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int q;
    cin >> q;
    vector<vector<pair<int,int>>> qr(n);
    for(int i=0;i<q;i++){
        int l,r;
        cin >> l >> r;
        l--,r--;
        qr[r].emplace_back(l,i);
    }
    SegmentTree<Monoid> seg(n);
    map<int,int> last;
    vector<int> ans(q);
    for(int i=0;i<n;i++){
        if(last.count(a[i])){
            int j=last[a[i]];
            seg.modify(j,make_pair(INF,-1));
            seg.modify(i,make_pair(j+1,a[i]));
        }else{
            seg.modify(i,make_pair(0,a[i]));
        }
        last[a[i]]=i;
        for(auto [l,j]:qr[i]){
            auto [pos,val]=seg.query(l,i);
            if(pos<=l){
                ans[j]=val;
            }
        }
    }
    for(auto x:ans){
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
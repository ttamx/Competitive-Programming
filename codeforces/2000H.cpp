#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/min.hpp"

const int X=2e6;
const int XX=4e6+5;

SegmentTree<MinMonoid<int>> seg(XX,INF);

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+2);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    a[n+1]=2*X+2;
    set<int> s;
    for(auto x:a)s.emplace(x);
    map<int,multiset<int>> ms;
    auto insert=[&](int l,int r){
        int d=r-l-1;
        if(d==0)return;
        auto &s=ms[d];
        s.emplace(l+1);
        int val=s.empty()?INF:*s.begin();
        seg.modify(d,val);
    };
    auto erase=[&](int l,int r){
        int d=r-l-1;
        if(d==0)return;
        auto &s=ms[d];
        auto it=s.find(l+1);
        assert(it!=s.end());
        s.erase(it);
        int val=s.empty()?INF:*s.begin();
        seg.modify(d,val);
    };
    for(int i=0;i<=n;i++){
        insert(a[i],a[i+1]);
    }
    int q;
    cin >> q;
    while(q--){
        char op;
        int x;
        cin >> op >> x;
        if(op=='+'){
            auto it=s.emplace(x).first;
            int l=*prev(it),r=*next(it);
            erase(l,r);
            insert(l,x);
            insert(x,r);
        }else if(op=='-'){
            auto it=s.erase(s.find(x));
            int l=*prev(it),r=*it;
            erase(l,x);
            erase(x,r);
            insert(l,r);
        }else{
            cout << seg.query(x,XX-1) << " ";
        }
    }
    cout << "\n";
    for(auto [x,_]:ms)seg.modify(x,INF);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/min-add.hpp"

const int X=1e6+5;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    set<int> start,vals;
    multiset<int> vals2;
    vector<int> cnt(X);
    Fenwick<ll> fen(X);
    SegmentTree<MinMonoid<ll>> seg_min(X,LINF);
    LazySegmentTree<MinAddAction<ll>> seg(X,0LL);
    auto recalc=[&](set<int>::iterator it){
        if(it==vals.end())return;
        int i=*it;
        ll d=(it==vals.begin()?LINF:(i-*prev(it)));
        seg_min.modify(i,d);
    };
    auto insert=[&](int i){
        vals2.emplace(i);
        if(cnt[i]==0){
            auto [it,inserted]=vals.emplace(i);
            assert(inserted);
            recalc(it);
            recalc(next(it));
            seg.update(i,i,-i);
        }else if(cnt[i]==1){
            seg_min.modify(i,0);
        }
        fen.update(i,i);
        seg.update(i+1,X-1,i);
        cnt[i]++;
    };
    auto erase=[&](int i){
        assert(cnt[i]>0);
        vals2.erase(vals2.find(i));
        if(cnt[i]==1){
            auto it=vals.find(i);
            assert(it!=vals.end());
            seg_min.modify(i,LINF);
            recalc(vals.erase(it));
            seg.update(i,i,i);
        }else if(cnt[i]==2){
            auto it=vals.find(i);
            assert(it!=vals.end());
            recalc(it);
            start.erase(i);
        }
        fen.update(i,-i);
        seg.update(i+1,X-1,-i);
        cnt[i]--;
    };
    auto solve=[&]()->bool {
        if(vals2.size()<=1)return true;
        ll mx=*prev(vals2.end(),2);
        int cur=0;
        while(cur<mx){
            int new_cur=seg.findfirst(cur+1,X-1,[&](ll x){return x<0;})-1;
            cerr << "(1) " << cur << " -> " << new_cur << "\n";
            cur=max(cur,new_cur);
            if(cur>=mx)break;
            ll sum=fen.query(cur);
            new_cur=seg_min.findlast(cur+2,X-1,[&](ll x){return x<=sum;});
            cerr << "(2) " << cur << " -> " << new_cur << "\n";
            if(new_cur<=cur)break;
            cur=new_cur;
        }
        return cur>=mx;
    };
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        insert(x);
    }
    for(auto x:vals){
        cerr << "(" << x << ", " << seg_min.query(x,x) << ") "; 
    }
    cerr << "\n";
    cout << (solve()?"Yes":"No") << "\n";
    while(q--){
        char op;
        int x;
        cin >> op >> x;
        if(op=='+'){
            insert(x);
        }else{
            erase(x);
        }
        for(auto x:vals){
            cerr << "(" << x << ", " << seg_min.query(x,x) << ") "; 
        }
        cerr << "\n";
        cout << (solve()?"Yes":"No") << "\n";
    }
}
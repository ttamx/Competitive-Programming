#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"

struct Info_{
    array<int,20> a;
    int sz;
    Info_():sz(0){
        fill(a.begin(),a.end(),0);
    }
    Info_(int x):sz(1){
        for(int i=0;i<20;i++){
            a[i]=x>>i&1;
        }
    }
};

struct InfoMonoid_{
    using value_type = Info_;
    static Info_ op(const Info_ &x,const Info_ &y){
        Info_ res;
        for(int i=0;i<20;i++){
            res.a[i]=x.a[i]+y.a[i];
        }
        res.sz=x.sz+y.sz;
        return res;
    }
    static Info_ unit(){
        return Info_();
    }
};

struct TagMonoid_{
    using value_type = int;
    static int op(const int &x,const int &y){
        return x^y;
    }
    static int unit(){
        return 0;
    }
};

struct Action{
    using InfoMonoid = InfoMonoid_;
    using TagMonoid = TagMonoid_;
    using Info = Info_;
    using Tag = int;
    static Info op(const Info &x,const Tag &y){
        auto res=x;
        for(int i=0;i<20;i++){
            if(y>>i&1){
                res.a[i]=res.sz-res.a[i];
            }
        }
        return res;
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    LazySegmentTree<Action> seg(a);
    int q;
    cin >> q;
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int l,r;
            cin >> l >> r;
            l--,r--;
            auto res=seg.query(l,r);
            ll ans=0;
            for(int i=0;i<20;i++){
                ans+=ll(res.a[i])<<i;
            }
            cout << ans << "\n";
        }else{
            int l,r,x;
            cin >> l >> r >> x;
            l--,r--;
            seg.update(l,r,x);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
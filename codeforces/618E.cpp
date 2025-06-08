#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"

using T = complex<db>;
using P = pair<T,T>;

struct DummyMonoid{
    using value_type = T;
    static T op(const T &x,const T &y){return x+y;}
    static T unit(){return T(0);}
};

// f(x) = a * x + b;
struct TagMonoid{
    using value_type = P;
    static P op(const P &x,const P &y){return P(x.first*y.first,x.second*y.first+y.second);}
    static P unit(){return P(1,0);}
};

struct Action{
    using InfoMonoid = DummyMonoid;
    using TagMonoid = ::TagMonoid;
    using Info = T;
    using Tag = P;
    static Info op(const Info &a,const Tag &b){return a*b.first+b.second;}
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    LazySegmentTree<Action> seg(n+1,[&](int i){return T(i);});
    cout << fixed << setprecision(10);
    auto get=[&](int i){
        return seg.query(i,i);
    };
    while(q--){
        int t,x,val;
        cin >> t >> x >> val;
        T u=get(x-1),v=get(x);
        if(t==1){
            T d=v-u;
            d*=db(val)/abs(d);
            seg.update(x,n,P(1,d));
        }else{
            P cur(1,-u);
            cur=TagMonoid::op(cur,P(exp(T(0,db(360-val)*PI/180.0)),0));
            cur.second+=u;
            seg.update(x,n,cur);
        }
        T ans=get(n);
        cout << real(ans) << " " << imag(ans) << "\n";
    }
}
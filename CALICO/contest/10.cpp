#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/add-count-add.hpp"

struct Mono{
    using value_type = ll;
    static constexpr ll op(const ll &x,const ll &y){return gcd(x,y);}
    static constexpr ll unit(){return 0LL;}
};

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n),b(n-1);
    for(auto &x:a){
        cin >> x;
    }
    for(int i=0;i<n-1;i++){
        b[i]=a[i+1]-a[i];
    }
    SegmentTree<Mono> seg(n-1,[&](int i){return abs(b[i]);});
    LazySegmentTree<AddCountAddAction<ll>> seg2(n,[&](int i){return make_pair(a[i],1);});
    auto query=[&](int l,int r){
        ll res=seg2.query(l,l).first;
        if(l<r){
            res=gcd(res,seg.query(l,r-1));
        }
        return res;
    };
    auto safe_div=[&](ll x,ll y){
        if(x==0)return 0LL;
        assert(x%y==0);
        return x/y;
    };
    int q;
    cin >> q;
    while(q--){
        string op;
        cin >> op;
        if(op=="FIND"){
            if(seg2.query(0,n-1).first==0){
                cout << 0 << "\n";
                continue;
            }
            ll pref=seg2.query(0,0).first;
            ll ans=safe_div(seg2.query(0,0).first,pref)+safe_div(seg2.query(1,n-1).first,query(1,n-1));
            auto update=[&](int i){
                if(i==-1)return;
                if(i<n-2){
                    ans=min(ans,safe_div(seg2.query(0,i+1).first,query(0,i+1))+safe_div(seg2.query(i+2,n-1).first,query(i+2,n-1)));
                }else{
                    ans=min(ans,safe_div(seg2.query(0,n-1).first,query(0,i+1)));
                }
            };
            for(int i=0;i<n-1;i++){
                pref=query(0,i+1);
                int l=i,r=n-2;
                while(l<r){
                    int m=(l+r+1)/2;
                    if(query(0,m+1)==pref){
                        l=m;
                    }else{
                        r=m-1;
                    }
                }
                i=l;
                update(i);
            }
            ll suf=seg2.query(n-2,n-2).first;
            update(n-2);
            for(int i=n-1;i>=0;i--){
                suf=query(i,n-1);
                int l=0,r=i;
                while(l<r){
                    int m=(l+r)/2;
                    if(query(m,n-1)==suf){
                        r=m;
                    }else{
                        l=m+1;
                    }
                }
                i=l;
                update(i-2);
            }
            cout << ans << "\n";
        }else{
            int l,r;
            ll x;
            cin >> l >> r >> x;
            l--,r--;
            seg2.update(l,r,x);
            if(l>0){
                b[l-1]+=x;
                seg.modify(l-1,abs(b[l-1]));
            }
            if(r<n-1){
                b[r]-=x;
                seg.modify(r,abs(b[r]));
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
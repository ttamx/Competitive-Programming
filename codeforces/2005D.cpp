#include "template.hpp"
#include "data-structure/sparse-table.hpp"
#include "group/monoid/monoid-base.hpp"

int op(int a,int b){
    return gcd(a,b);
}

int e(){
    return 0;
}

using Mono = MonoidBase<int,op,e>;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    auto pa=a,pb=b,sa=a,sb=b;
    for(int i=1;i<n;i++){
        pa[i]=gcd(pa[i],pa[i-1]);
        pb[i]=gcd(pb[i],pb[i-1]);
    }
    for(int i=n-2;i>=0;i--){
        sa[i]=gcd(sa[i],sa[i+1]);
        sb[i]=gcd(sb[i],sb[i+1]);
    }
    SparseTable<Mono> ta(a),tb(b);
    auto getpos=[&](int i){
        vector<int> res;
        for(int j=i;j>=0;j--){
            int l=0,r=j;
            int val=ta.query(j,i)+tb.query(j,i);
            while(l<r){
                int m=(l+r)/2;
                if(ta.query(m,i)+tb.query(m,i)==val)r=m;
                else l=m+1;
            }
            res.emplace_back(j);
            j=l;
        }
        return res;
    };
    int ans=0;
    ll ans2=0;
    for(int i=0;i<n;i++){
        auto pos=getpos(i);
        pos.emplace_back(-1);
        for(int j=1;j<pos.size();j++){
            auto calc=[&](int x){
                int va=gcd(x?pa[x-1]:0,tb.query(pos[j]+1,i));
                int vb=gcd(x?pb[x-1]:0,ta.query(pos[j]+1,i));
                if(i+1<n){
                    va=gcd(va,sa[i+1]);
                    vb=gcd(vb,sb[i+1]);
                }
                return va+vb;
            };
            int val=calc(pos[j]+1);
            int l=pos[j]+1,r=pos[j-1];
            while(l<r){
                int m=(l+r+1)/2;
                if(calc(m)==val)l=m;
                else r=m-1;
            }
            if(val>ans){
                ans=val;
                ans2=l-pos[j];
            }else if(val==ans){
                ans2+=l-pos[j];
            }
        }
    }
    cout << ans << " " << ans2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
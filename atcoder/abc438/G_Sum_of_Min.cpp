#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    ll k;
    cin >> n >> m >> k;
    int g=gcd(n,m);
    int nn=n/g,mm=m/g;
    vector<ll> a(n),b(m);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    mint ans=0;
    for(int tt=0;tt<2;tt++){
        for(int s=0;s<g;s++){
            vector<ll> aa,bb;
            for(int i=s;i<n;i+=g)aa.emplace_back(a[i]);
            vector<int> ord(mm);
            for(int t=0,i=s;t<mm;t++,i=(i+n)%m){
                bb.emplace_back(b[i]);
                ord[i/g]=t;
            }
            auto cb=bb;
            sort(cb.begin(),cb.end());
            vector<vector<pair<int,mint>>> event(mm);
            auto insert=[&](int l,int r,int x){
                if(l)event[l-1].emplace_back(x,-1);
                event[r].emplace_back(x,1);
            };
            for(int i=0;i<nn;i++){
                int x=s+i*g;
                if(x>=k)continue;
                ll t=(k-x-1)/n;
                ll mul=t/mm;
                t%=mm;
                ans+=mint(aa[i])*mint(mul)*mint(cb.end()-upper_bound(cb.begin(),cb.end(),aa[i]));
                int l=ord[i%mm];
                int r=l+t;
                if(r<mm){
                    insert(l,r,aa[i]);
                }else{
                    insert(l,mm-1,aa[i]);
                    insert(0,r-mm,aa[i]);
                }
            }
            Fenwick<int> f(mm+1);
            for(int i=0;i<mm;i++){
                f.update(lower_bound(cb.begin(),cb.end(),bb[i])-cb.begin(),+1);
                for(auto [x,mul]:event[i]){
                    ans+=mint(x)*mul*mint(f.query(upper_bound(cb.begin(),cb.end(),x)-cb.begin(),mm));
                }
            }
        }
        swap(a,b);
        swap(n,m);
        swap(nn,mm);
        for(auto &x:b)x++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
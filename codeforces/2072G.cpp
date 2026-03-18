#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    ll n,k;
    cin >> n >> k;
    mint ans=0;
    if(k>n){
        ans+=mint(k-n)*n;
        k=n;
    }
    ll cur=2;
    for(;cur<=k&&cur*cur<=n;cur++){
        vector<ll> a;
        for(ll x=n;x>0;x/=cur){
            a.emplace_back(x%cur);
        }
        mint val=0;
        for(auto x:a){
            val=val*cur+x;
        }
        ans+=val;
    }
    for(;cur<=k;cur++){
        ll d=n/cur;
        ll v=n%cur;
        ll s=v/d;
        s=min(s,k-cur);
        ans+=mint(v*cur+d)*(s+1)+(v-d*cur)*mint(s*(s+1)/2)-d*mint(s*(s+1)*(2*s+1)/6);
        cur+=s;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
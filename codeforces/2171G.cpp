#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

const int M=1000003;

using mint = MontgomeryModInt<M,0>;

Combinatorics<mint> comb;

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
    int mn=INF;
    for(int i=0;i<n;i++){
        int c=0;
        while((a[i]<<(c+1))<=b[i]){
            c++;
        }
        mn=min(mn,c);
    }
    ll ans=mn;
    mint ways=1;
    vector<ll> cnt(mn+1);
    for(int i=0;i<n;i++){
        int x=b[i];
        for(int j=mn;j>=1;j--){
            if(x&1){
                ans++;
                cnt[j]++;
            }
            x>>=1;
        }
        x-=a[i];
        assert(x>=0);
        ans+=x;
        cnt[0]+=x;
        ways*=comb.ifac(x);
    }
    for(int i=1;i<=mn;i++){
        ways*=comb.fac(cnt[i]);
    }
    if(cnt[0]>=M){
        ways=0;
    }else{
        ways*=comb.fac(cnt[0]);
    }
    cout << ans << " " << ways << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
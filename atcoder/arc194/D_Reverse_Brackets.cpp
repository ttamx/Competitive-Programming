#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

const ll P=940539289;
const ll BASE1=120918643;
const ll BASE2=151511309;

ll hasher(const vector<ll> &a){
    ll res=0;
    for(auto x:a){
        res=(res*BASE1)+x%P;
    }
    return (res*BASE1+BASE2)%P;
}

const int N=5005;

int n;
string s;
map<ll,mint> dp;

ll solve(int l,int r){
    int bal=0,last=l;
    vector<ll> a;
    map<ll,int> cnt;
    int ch=0;
    for(int i=l+1;i<r;i++){
        bal+=(s[i]=='('?1:-1);
        if(bal==0){
            ll val=solve(last+1,i);
            cnt[val]++;
            a.emplace_back(val);
            ch++;
            last=i;
        }
    }
    assert(bal==0);
    sort(a.begin(),a.end());
    ll cur_hash=hasher(a);
    mint &res=dp[cur_hash];
    res=comb.fac(ch);
    for(auto [h,c]:cnt){
        mint ways=dp[h];
        for(int i=0;i<c;i++){
            res*=ways;
        }
        res*=comb.ifac(c);
    }
    return cur_hash;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    cin >> s;
    s="("+s+")";
    cout << dp[solve(0,n+1)];
}
#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

const int N=1e5+5;

int mob[N];
vector<int> factor[N];

void runcase(){
    int n;
    cin >> n;
    vector<mint> dp(n+1),aux(n+1);
    auto upd=[&](int i,mint v){
        dp[i]+=v;
        for(auto d:factor[i]){
            aux[d]+=v;
        }
    };
    for(int i=n;i>=1;i--){
        vector<pair<int,mint>> to_upd;
        for(auto g:factor[i]){
            mint res=0;
            for(auto d:factor[i/g]){
                res+=mob[d]*aux[d*g];
            }
            to_upd.emplace_back(g,res-dp[g]);
        }
        for(auto [g,v]:to_upd){
            upd(g,v*2);
        }
        upd(i,1);
    }
    mint ans=0;
    for(auto v:dp){
        ans+=v;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<N;i++){
        mob[i]=1;
    }
    for(int i=1;i<N;i++){
        for(int j=i;j<N;j+=i){
            factor[j].emplace_back(i);
        }
        if(factor[i].size()==2){
            for(int j=i;j<N;j+=i){
                mob[j]*=-1;
            }
            ll v=1LL*i*i;
            for(ll j=v;j<N;j+=v){
                mob[j]=0;
            }
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}
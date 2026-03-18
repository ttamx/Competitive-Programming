#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

struct DS{;
    mint add,mul,sum,sz;
    map<int,mint> dat;
    DS():add(0),mul(1),sum(0),sz(0),dat{}{}
    void insert(int i){
        dat[i]=-add*mul;
        sz++;
    }
    void erase(int i){
        sum-=dat[i]*mul+add;
        dat.erase(i);
        sz--;
    }
    void upd_add(mint x){
        sum+=x*sz;
        add+=x;
    }
    void upd_mul(mint x){
        add*=x;
        mul*=x;
        sum*=x;
    }
};

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> add(n+1),del(n+1);
    for(int i=0;i<m;i++){
        int l,r;
        cin >> l >> r;
        add[l].emplace_back(i);
        del[r].emplace_back(i);
    }
    DS ds[2];
    vector<mint> dp(n+1);
    dp[0]=1;
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1]+ds[i&1].sum;
        for(auto j:add[i]){
            ds[0].insert(j);
            ds[1].insert(j);
        }
        ds[i&1^1].upd_mul(-1);
        ds[i&1^1].upd_add(dp[i-1]);
        for(auto j:del[i]){
            ds[0].erase(j);
            ds[1].erase(j);
        }
    }
    cout << dp[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
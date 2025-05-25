#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

mint catalan(int n){
    return comb.fac(2*n)*comb.ifac(n)*comb.ifac(n+1);
}

mint icatalan(int n){
    return comb.ifac(2*n)*comb.fac(n)*comb.fac(n+1);
}

void runcase(){
    int n;
    cin >> n;
    vector<bool> op(2*n);
    vector<int> id(2*n);
    vector<int> par(n+1),cnt(n+1),fa(n+1);
    iota(fa.begin(),fa.end(),0);
    cnt[0]=n+1;
    for(int i=1;i<=n;i++){
        int l,r;
        cin >> l >> r;
        l--,r--;
        op[l]=true;
        id[l]=i;
        cnt[i]=(r-l+1)/2;
    }
    stack<int> s;
    s.emplace(0);
    for(int i=0;i<2*n;i++){
        if(op[i]){
            int u=id[i],p=s.top();
            cnt[p]-=cnt[u];
            par[u]=p;
            s.emplace(u);
        }else{
            s.pop();
        }
    }
    mint base=1;
    function<int(int)> fp=[&](int u){
        return fa[u]=u==fa[u]?u:fp(fa[u]);
    };
    auto uni=[&](int u,int v){
        u=fp(u),v=fp(v);
        base*=icatalan(cnt[u]-1);
        base*=icatalan(cnt[v]-1);
        cnt[u]+=cnt[v];
        fa[v]=u;
        base*=catalan(cnt[u]-1);
    };
    vector<mint> ans{1};
    for(int i=n;i>=1;i--){
        uni(par[i],i);
        ans.emplace_back(base);
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
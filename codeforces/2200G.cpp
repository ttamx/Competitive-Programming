#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

void runcase(){
    int n;
    mint st;
    cin >> n >> st;
    vector<mint> a;
    mint sum=0;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        mint v=stoi(s.substr(1));
        if(s[0]=='+')sum+=v;
        else if(s[0]=='-')sum-=v;
        else if(s[0]=='x')a.emplace_back(v);
        else a.emplace_back(v.inv());
    }
    int m=a.size();
    vector<mint> dp(m+1);
    dp[0]=1;
    for(auto x:a){
        for(int i=m;i>=1;i--){
            dp[i]+=dp[i-1]*x;
        }
    }
    mint ans=st*dp[m]*comb.fac(n);
    if(m<n){
        for(int i=0;i<=m;i++){
            ans+=sum*comb.C(n,m+1)*comb.fac(i)*comb.fac(m-i)*comb.fac(n-m-1)*dp[i];
        }
    }
    cout << ans*comb.ifac(n) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
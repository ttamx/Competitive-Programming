#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int k=0;
    for(auto x:a)if(x==0)k++;
    int cnt=0;
    for(int i=0;i<k;i++)if(a[i]==0)cnt++;
    vector<mint> dp(k+1);
    dp[cnt]=0;
    mint tot=mint(n)*mint(n-1)/2;
    for(int i=cnt;i<k;i++){
        mint res=mint(k-i)*mint(k-i);
        dp[i+1]=dp[i]+tot/res;
    }
    cout << dp[k] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const mint INV=mint(10000).inv();

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    array<mint,1024> dp;
    dp[0]=1;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        mint p=mint(x)*INV;
        mint q=1-p;
        array<mint,1024> ndp;
        for(int j=0;j<1024;j++){
            ndp[j^a[i]]+=dp[j]*p;
            ndp[j]+=dp[j]*q;
        }
        swap(dp,ndp);
    }
    mint ans=0;
    for(int i=0;i<1024;i++){
        mint x=i;
        ans+=dp[i]*x*x;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    if(a[0]>1){
        cout << "0\n";
        return;
    }
    vector<vector<int>> factor(m+1);
    for(int i=1;i<=m;i++){
        for(int j=i;j<=m;j+=i){
            if(i+j<=m)factor[j].emplace_back(i);
        }
    }
    vector<mint> dp(m+1);
    dp[1]=1;
    for(int t=1;t<n;t++){
        vector<mint> ndp(m+1);
        for(int i=1;i<=m;i++){
            for(auto j:factor[i]){
                ndp[i+j]+=dp[i];
            }
        }
        dp=move(ndp);
        if(a[t]){
            for(int i=1;i<=m;i++){
                if(i!=a[t]){
                    dp[i]=0;
                }
            }
        }
    }
    cout << accumulate(dp.begin(),dp.end(),mint(0)) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
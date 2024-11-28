#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int mx=*max_element(a.begin(),a.end());
    vector<vector<int>> factor(mx+1);
    vector<int> mob(mx+1,1);
    for(int i=1;i<=mx;i++){
        for(int j=i;j<=mx;j+=i){
            factor[j].emplace_back(i);
        }
        if(factor[i].size()==2){
            for(int j=i;j<=mx;j+=i){
                mob[j]=-mob[j];
            }
            ll v=1LL*i*i;
            for(ll j=v;j<=mx;j+=v){
                mob[j]=0;
            }
        }
    }
    vector<mint> dp(n),dp2(mx+1);
    for(int i=0;i<n;i++){
        if(i==0){
            dp[0]=1;
        }else{
            for(int j:factor[a[i]]){
                dp[i]+=dp2[j];
            }
            dp[i]-=dp2[1];
        }
        for(int j:factor[a[i]]){
            dp2[j]-=dp[i]*mob[j];
        }
    }
    cout << dp[n-1] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
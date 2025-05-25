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
    if(n==1){
        return void(cout << (a[0]?1:2) << "\n");
    }
    vector<mint> dp(n);
    for(int i=0;i<n;i++){
        if(i==0){
            if(a[i]==0){
                dp[i]=1;
            }
        }else if(i==1){
            if(a[i]==1){
                dp[i]=1;
            }
            if(a[i]==a[i-1]){
                dp[i]+=dp[i-1];
            }
        }else{
            if(a[i]==a[i-1]){
                dp[i]+=dp[i-1];
            }
            if(a[i]==1+a[i-2]){
                dp[i]+=dp[i-2];
            }
        }
    }
    cout << dp[n-1]+dp[n-2] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
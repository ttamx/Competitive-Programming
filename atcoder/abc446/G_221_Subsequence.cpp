#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<int> ptr(n+1);
    vector<queue<int>> q(n+1);
    vector<mint> dp(n+1);
    dp[0]=1;
    mint ans=0;
    for(int i=1;i<=n;i++){
        q[a[i]].emplace(i);
        if(q[a[i]].size()==a[i]){
            int j=q[a[i]].front();
            q[a[i]].pop();
            for(int &k=ptr[a[i]];k<j;k++){
                if(a[k]==a[i])continue;
                dp[i]+=dp[k];
            }
        }
        ans+=dp[i];
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
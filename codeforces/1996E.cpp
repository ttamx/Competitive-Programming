#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    mint ans=0;
    map<int,mint> dp;
    int cur=0;
    dp[0]=1;
    for(int i=0;i<n;i++){
        cur+=(s[i]=='1'?1:-1);
        ans+=dp[cur]*(n-i);
        dp[cur]+=i+2;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
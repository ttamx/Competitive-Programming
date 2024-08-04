#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> n >> m;
    string s;
    cin >> s;
    s="P"+s+"S";
    vector<ll> b(n+2);
    for(int i=1;i<=n;i++){
        cin >> b[i];
    }
    set<ll> val;
    for(int i=0;i<=n;i++){
        val.emplace(b[i]+b[i+1]);
    }
    mint ans=0;
    for(auto sum:val){
        vector<mint> dp(2);
        if(s[1]=='P'||s[1]=='?'){
            if(abs(b[1])<=m){
                dp[0]++;
            }
        }
        if(s[1]=='S'||s[1]=='?'){
            if(b[1]==sum){
                dp[1]++;
            }
        }
        for(int i=2;i<=n+1;i++){
            vector<mint> ndp(2);
            if(s[i]=='P'||s[i]=='?'){
                if(abs(b[i]-b[i-1])<=m){ // PP
                    ndp[0]+=dp[0];
                }
                if(abs(b[i]+b[i-1]-sum)<=2*m){ // SP
                    ndp[0]+=dp[1];
                }
            }
            if(s[i]=='S'||s[i]=='?'){
                if(b[i-1]+b[i]==sum){ // PS
                    ndp[1]+=dp[0];
                }
                if(abs(b[i-1]-b[i])<=m){ // SS
                    ndp[1]+=dp[1];
                }
            }
            swap(dp,ndp);
        }
        ans+=dp[1];
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
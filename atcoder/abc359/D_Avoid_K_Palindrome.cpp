#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    int m=1<<k;
    vector<mint> dp(m);
    vector<int> bad;
    for(int i=0;i<m;i++){
        int rev=0;
        for(int j=0;j<k;j++){
            rev|=(i>>j&1)<<(k-j-1);
        }
        if(i==rev)bad.emplace_back(i);
    }
    for(int i=0;i<m;i++){
        dp[i]=1;
        for(int j=0;j<k;j++){
            if(s[j]!='?'&&s[j]-'A'!=(i>>j&1)){
                dp[i]=0;
                break;
            }
        }
    }
    for(auto j:bad)dp[j]=0;
    for(int i=k;i<n;i++){
        vector<mint> ndp(m);
        if(s[i]=='A'||s[i]=='?'){
            for(int j=0;j<m;j++){
                ndp[j>>1]+=dp[j];
            }
        }
        if(s[i]=='B'||s[i]=='?'){
            for(int j=0;j<m;j++){
                ndp[(j>>1)|(m>>1)]+=dp[j];
            }
        }
        for(auto j:bad)ndp[j]=0;
        dp=ndp;
    }
    cout << accumulate(dp.begin(),dp.end(),mint(0)) << "\n";
}
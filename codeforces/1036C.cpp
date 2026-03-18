#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    auto solve=[&](ll x){
        string s=to_string(x);
        array<ll,4> dp{};
        int cnt=0;
        for(int i=0;i<s.size();i++){
            for(int j=2;j>=0;j--){
                dp[j+1]+=dp[j]*9;
            }
            if(s[i]>'0'){
                if(cnt<=3)dp[cnt]++;
                if(cnt<=2)dp[cnt+1]+=s[i]-'1';
            }
            if(s[i]!='0')cnt++;
        }
        return accumulate(dp.begin(),dp.end(),0LL);
    };
    ll l,r;
    cin >> l >> r;
    cout << solve(r+1)-solve(l) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
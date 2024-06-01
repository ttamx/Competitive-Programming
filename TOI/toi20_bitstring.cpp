#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    int m=1<<n;
    vector<long long> dp(m);
    auto get=[&](){
        string s;
        cin >> s;
        int mask=0;
        for(auto x:s)mask=mask<<1|(x=='1');
        return mask;
    };
    for(int i=0;i<m;i++)cin >> dp[get()];
    for(int mask=1;mask<m;mask++){
        long long res=-INF;
        int p=-2;
        for(int i=0;i<n;i++)if(mask>>i&1){
            res=max(res,dp[mask^(1<<i)]);
            if(p==i-1)res=max(res,dp[mask^(1<<i)^(1<<p)]);
            p=i;
        }
        dp[mask]+=res;
    }
    while(q--)cout << dp[get()] << "\n";
}
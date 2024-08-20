#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=1e18;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q,k;
    cin >> n >> q >> k;
    int b=1<<k;
    vector<ll> dp(b,INF);
    for(int i=0;i<n;i++){
        int s,c;
        cin >> s >> c;
        int mask=0;
        for(int i=0;i<s;i++){
            int x;
            cin >> x;
            mask|=1<<(x-1);
        }
        dp[mask]=min(dp[mask],(ll)c);
    }
    for(int i=b-1;i>=0;i--){
        for(int j=0;j<k;j++){
            if(i>>j&1){
                int x=i^(1<<j);
                dp[x]=min(dp[x],dp[i]);
            }
        }
    }
    for(int i=0;i<b;i++){
        for(int j=i;j>0;j=(j-1)&i){
            dp[i]=min(dp[i],dp[j]+dp[i^j]);
        }
    }
    while(q--){
        int s;
        cin >> s;
        int mask=0;
        for(int i=0;i<s;i++){
            int x;
            cin >> x;
            mask|=1<<(x-1);
        }
        cout << (dp[mask]<INF?dp[mask]:-1LL) << "\n";
    }
}
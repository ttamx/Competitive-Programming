#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    vector<int> c(4);
    for(auto &x:c)cin >> x;
    vector<ll> dp(100001);
    dp[0]=1;
    for(int i=0;i<4;i++)for(int j=c[i];j<=100000;j++)dp[j]+=dp[j-c[i]];
    int q;
    cin >> q;
    while(q--){
        vector<int> d(4);
        for(auto &x:d)cin >> x;
        int v;
        cin >> v;
        ll ans=dp[v];
        for(int i=1;i<16;i++){
            int res=v;
            for(int j=0;j<4;j++)if(i&(1<<j))res-=(d[j]+1)*c[j];
            if(res>=0)ans-=((__builtin_popcount(i)&1)?1:-1)*dp[res];
        }
        cout << ans << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
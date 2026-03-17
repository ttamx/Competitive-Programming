#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int MOD=1e9+7;

int t,k;
ll dp[N];
ll f[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t >> k;
    dp[0]=1;
    for(int i=1;i<N;i++){
        dp[i]=(dp[i-1]+(i>=k?dp[i-k]:0LL))%MOD;
        f[i]=(f[i-1]+dp[i])%MOD;
    }
    while(t--){
        int l,r;
        cin >> l >> r;
        cout << (f[r]-f[l-1]+MOD)%MOD << "\n";
    }
}
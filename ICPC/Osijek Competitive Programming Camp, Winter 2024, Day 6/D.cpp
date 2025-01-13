#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3e5+5;
const int B=60;
const ll MOD=1e9+7;

int n;
ll a[N];
ll dp[N];
ll aux[B][2];

void update(ll mask,ll val){
    ll mul=1;
    for(int i=0;i<B;i++){
        int s=mask>>i&1^1;
        aux[i][s]=(aux[i][s]+val*mul)%MOD;
        mul=mul*2%MOD;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]^=a[i-1];
    }
    update(0,1);
    for(int i=1;i<=n;i++){
        for(int j=0;j<B;j++){
            dp[i]=(dp[i]+aux[j][a[i]>>j&1])%MOD;
        }
        update(a[i],dp[i]);
    }
    cout << dp[n] << "\n";
}
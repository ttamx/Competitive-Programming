#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=998244353;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<ll> pw(k);
    pw[0]=1;
    for(int i=1;i<k;i++){
        pw[i]=pw[i-1]*2%MOD;
    }
    vector<int> mn(k,n+1);
    for(int i=1;i<=n;i++){
        ll x;
        cin >> x;
        for(int j=0;j<k;j++){
            if(x>>j&1){
                mn[j]=min(mn[j],i);
            }
        }
    }
    sort(mn.rbegin(),mn.rend());
    for(auto &x:mn)if(x>n)x=0;
    ll ans=0;
    for(int i=0;i<k;i++)ans=(ans+mn[i]*pw[i])%MOD;
    cout << ans << "\n";
}
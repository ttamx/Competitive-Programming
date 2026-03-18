#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void solve(){
    ll l,v0,T,n;
    cin >> l >> v0 >> T >> n;
    for(int i=1;i<=n;i++){
        ll t,v;
        cin >> t >> v;
        cout << (T-t)*abs(v-v0)/l+1 << " \n"[i==n];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve(){
    ll w,b;
    cin >> w >> b;
    ll l=0,r=1e5;
    while(l<r){
        ll m=(l+r+1)/2;
        ll tar=m*(m+1)/2;
        ll c=w;
        for(ll i=m;i>=1;i--){
            if(c>=i){
                c-=i;
                tar-=i;
            }
        }
        if(tar<=b)l=m;
        else r=m-1;
    }
    cout << l << "\n";
}

signed main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
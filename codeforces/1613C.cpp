#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        ll n,h;
        cin >> n >> h;
        vector<ll> a(n);
        for(auto &x:a)cin >> x;
        ll l=0,r=h;
        while(l<r){
            ll m=(l+r)/2;
            ll cur=m;
            for(int i=1;i<n;i++){
                cur+=min(m,a[i]-a[i-1]);
            }
            if(cur>=h)r=m;
            else l=m+1;
        }
        cout << l << "\n";
    }
}
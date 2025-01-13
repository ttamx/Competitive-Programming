#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n,k,x;
    cin >> n >> k >> x;
    vector<ll> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
    }
    auto check=[&](ll cur){
        vector<ll> c;
        for(int i=0;i<n;i++){
            c.emplace_back(max(0LL,a[i]-cur)*b[i]);
        }
        sort(c.rbegin(),c.rend());
        ll cost=0;
        while(c.size()+1>x){
            cost+=c.back();
            c.pop_back();
        }
        return cost<k;
    };
    ll l=0,r=1e6;
    while(l<r){
        ll m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    cout << l;
}
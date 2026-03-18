#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<ll> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    auto check=[&](ll m){
        ll cur=k;
        for(int i=0;i<n;i++){
            cur-=max(0LL,1LL*a[i]*m-b[i]);
            if(cur<0)return false;
        }
        return true;
    };
    ll l=0,r=2e9;
    while(l<r){
        ll m=(l+r+1)/2;
        if(check(m))l=m;
        else r=m-1;
    }
    cout << l << "\n";
}
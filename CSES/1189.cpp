#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    for(int i=1;i<n;i++)a[i]+=a[i-1];
    for(int i=1;i<n;i++)b[i]+=b[i-1];
    for(int i=0;i<n;i++)a[i]-=b[i];
    sort(a.begin(),a.end());
    ll m=a[a.size()/2];
    ll ans=0;
    for(auto x:a)ans+=abs(x-m);
    cout << ans << "\n";
}
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    ll mx=a.back();
    ll mn=a[0];
    ll ans=0;
    for(int i=1;i<n;i++){
        ans+=max(a[i]-mn,mx-a[i]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
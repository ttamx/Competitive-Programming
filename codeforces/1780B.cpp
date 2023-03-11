#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n+1);
    for(int i=1;i<=n;i++)cin >> a[i],a[i]+=a[i-1];
    ll ans=1;
    for(int i=1;i<n;i++)ans=max(ans,gcd(a[i],a[n]));
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
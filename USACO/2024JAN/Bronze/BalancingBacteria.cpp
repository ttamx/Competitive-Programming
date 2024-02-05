#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    ll ans=0,add=0,lz=0;
    for(int i=1;i<=n;i++){
        a[i]+=lz+add*i;
        ans+=abs(a[i]);
        add-=a[i];
        lz+=(i-1)*a[i];
    }
    cout << ans << "\n";
}
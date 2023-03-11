#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<ll,ll> p2;
 
void runcase(){
    ll n,l;
    cin >> n >> l;
    vector<ll> w(n),h(n);
    for(auto &x:w)cin >> x;
    for(auto &x:h)cin >> x;
    sort(h.rbegin(),h.rend());
    ll ans=0;
    for(ll i=0;i<n;i+=l)ans+=h[i];
    cout << ans << '\n';
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();   
}
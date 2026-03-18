#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    ll n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    map<ll,ll> cnt;
    cnt[0]++;
    ll sum=0;
    ll ans=0;
    for(ll i=1;i<=n;i++){
        ans+=1LL*i*(n-i+1);
    }
    for(auto x:a){
        sum^=x;
        ll c=cnt[sum];
        ans-=c*(c+1)/2;
        cnt[sum]++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}
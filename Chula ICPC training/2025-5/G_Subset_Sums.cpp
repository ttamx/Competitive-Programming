#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    ll lo,hi;
    cin >> n >> lo >> hi;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int h1=n/2;
    int h2=n-h1;
    vector<ll> b;
    for(int mask=0;mask<1<<h1;mask++){
        ll sum=0;
        for(int i=0;i<h1;i++){
            if(mask>>i&1){
                sum+=a[i];
            }
        }
        b.emplace_back(sum);
    }
    sort(b.begin(),b.end());
    ll ans=0;
    for(int mask=0;mask<1<<h2;mask++){
        ll sum=0;
        for(int i=0;i<h2;i++){
            if(mask>>i&1){
                sum+=a[i+h1];
            }
        }
        ans+=upper_bound(b.begin(),b.end(),hi-sum)-lower_bound(b.begin(),b.end(),lo-sum);
    }
    cout << ans << "\n";
}
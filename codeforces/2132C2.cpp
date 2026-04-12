#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    ll n,k;
    cin >> n >> k;
    vector<ll> a;
    ll ans=0,base=1;
    for(int i=0;n>0;i++){
        ll x=n%3;
        a.emplace_back(x);
        ans+=x*(base*3+i*base/3);
        k-=x;
        n/=3;
        base*=3;
    }
    if(k<0){
        cout << -1 << "\n";
        return;
    }
    k/=2;
    base/=3;
    for(int i=(int)a.size()-1;i>=1;i--){
        base/=3;
        ll used=min(k,a[i]);
        ans-=used*base;
        k-=used;
        a[i-1]+=3*used;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
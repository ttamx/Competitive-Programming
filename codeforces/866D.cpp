#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
ll ans;
multiset<ll> ms;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        ll p;
        cin >> p;
        ans-=p;
        ms.emplace(p);
        ms.emplace(p);
        ms.erase(ms.begin());
    }
    for(auto x:ms)ans+=x;
    cout << ans;
}
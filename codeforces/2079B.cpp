#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=1e18;

void solve(){
    int n,m;
    cin >> n >> m;
    vector<ll> a(m);
    for(auto &x:a){
        cin >> x;
    }
    reverse(a.begin(),a.end());
    multiset<ll,greater<ll>> pq;
    ll base=0;
    for(int i=0;i<m;i++){
        if(i%2==0){
            pq.emplace(2*a[i]);
            base-=a[i];
            base+=*pq.begin();
            pq.erase(pq.begin());
            if(1+2*pq.size()>n){
                pq.erase(prev(pq.end()));
            }
        }else{
            pq.emplace(2*a[i]);
            base-=a[i];
            if(2*pq.size()>n){
                pq.erase(prev(pq.end()));
            }
        }
    }
    ll ans=base;
    for(auto x:pq){
        base+=x;
        ans=max(ans,base);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}
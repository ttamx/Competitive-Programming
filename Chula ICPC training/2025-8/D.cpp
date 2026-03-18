#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    ll ans=0;
    priority_queue<ll> pq;
    for(int i=0;i<n;i++){
        ll x;
        cin >> x;
        ans-=x;
        pq.emplace(-x);
        pq.emplace(-x);
        pq.pop();
    }
    while(!pq.empty()){
        ans-=pq.top();
        pq.pop();
    }
    cout << ans << "\n";
}
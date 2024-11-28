#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;
    for(int i=0;i<n;i++){
        ll x;
        cin >> x;
        pq.emplace(x&-x,x);
    }
    while(pq.size()>1){
        ll x=pq.top().second;
        pq.pop();
        ll y=pq.top().second;
        pq.pop();
        ll z=2*gcd(x,y);
        pq.emplace(z&-z,z);
    }
    cout << pq.top().second;
}
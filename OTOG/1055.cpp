#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;
    set<ll> s;
    pq.emplace(0,0);
    s.emplace(0);
    while(k--){
        auto [d,u]=pq.top();
        pq.pop();
        if(k==0)cout << d,exit(0);
        for(int i=0;i<n;i++)if(s.emplace(u|(1LL<<i)).second)pq.emplace(d+a[i],u|(1LL<<i));
    }
}
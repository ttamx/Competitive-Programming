#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    ll ans=0,sum=0;
    priority_queue<ll,vector<ll>,greater<ll>> pq;
    for(int i=0;i<n;i++){
        if(pq.size()+1==k){
            ans=max(ans,sum+a[i]+i+1);
        }
        sum+=a[i];
        pq.emplace(a[i]);
        if(pq.size()==k){
            sum-=pq.top();
            pq.pop();
        }
    }
    cout << ans;
}

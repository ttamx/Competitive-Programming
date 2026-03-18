#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    ll base=0;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
        if(x<0){
            base+=x;
            x=-x;
        }
    }
    sort(a.begin(),a.end());
    using P = pair<ll,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    pq.emplace(base,n);
    pq.emplace(base+a[0],0);
    bool f=false;
    while(k>0){
        auto [v,i]=pq.top();
        pq.pop();
        if(v!=0||f){
            k--;
            cout << v << "\n";
        }else f=true;
        if(i+1<n){
            pq.emplace(v+a[i+1]-a[i],i+1);
            pq.emplace(v+a[i+1],i+1);
        }
    }
}
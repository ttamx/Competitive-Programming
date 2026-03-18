#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;

int n,k;
ll a[N],b[N];

pair<ll,ll> calc(ll lambda){
    using P = pair<ll,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    ll res=0;
    int cnt=0;
    for(int i=n;i>=1;i--){
        pq.emplace(b[i]-lambda,1);
        if(a[i]+pq.top().first<0){
            res+=a[i]+pq.top().first;
            cnt+=pq.top().second;
            pq.pop();
            pq.emplace(-a[i],0);
        }
    }
    return {res,cnt};
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    ll l=0,r=2e9;
    while(l<r){
        ll m=l+(r-l+1)/2;
        if(calc(m).second<=k)l=m;
        else r=m-1;
    }
    cout << calc(l).first+l*k << "\n";
}
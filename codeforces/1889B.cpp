#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,int> p2;

void runcase(){
    int n;
    ll c;
    cin >> n >> c;
    vector<ll> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    priority_queue<p2,vector<p2>,greater<p2>> pq;
    for(int i=2;i<=n;i++)pq.emplace(i*c-a[i],i);
    ll sum=a[1];
    while(!pq.empty()&&pq.top().first<=sum){
        auto [v,i]=pq.top();
        pq.pop();
        sum+=a[i];
    }
    cout << (pq.empty()?"Yes":"No") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
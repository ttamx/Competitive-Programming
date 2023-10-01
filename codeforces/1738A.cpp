#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    priority_queue<ll> pq[2];
    for(int i=0;i<n;i++)pq[a[i]].emplace(b[i]);
    int mn=min(pq[0].size(),pq[1].size());
    ll ans=0;
    if(mn*2<n){
        for(int i=0;i<mn;i++){
            ans+=2*pq[0].top();
            pq[0].pop();
            ans+=2*pq[1].top();
            pq[1].pop();
        }
        while(!pq[0].empty()){
            ans+=pq[0].top();
            pq[0].pop();
        }
        while(!pq[1].empty()){
            ans+=pq[1].top();
            pq[1].pop();
        }
    }else{
        mn--;
        for(int i=0;i<mn;i++){
            ans+=2*pq[0].top();
            pq[0].pop();
            ans+=2*pq[1].top();
            pq[1].pop();
        }
        ans+=pq[0].top()+pq[1].top();
        ans+=max(pq[0].top(),pq[1].top());
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x%=k;
    }
    int last=0;
    ll ans=0;
    priority_queue<ll,vector<ll>,greater<ll>> pq;
    for(auto x:a){
        if(x==last){
            continue;
        }
        int d=(x-last+k)%k;
        ans+=d;
        pq.emplace(d);
        if(x>last){
            pq.pop();
        }
        last=x;
    }
    while(!pq.empty()){
        ans-=pq.top();
        pq.pop();
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}
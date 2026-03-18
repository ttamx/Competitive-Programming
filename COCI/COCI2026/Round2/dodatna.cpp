#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<pair<int,int>> a(n);
    for(auto &[l,r]:a){
        cin >> l >> r;
    }
    sort(a.begin(),a.end());
    priority_queue<int,vector<int>,greater<int>> pq;
    int ans=0;
    for(auto [l,r]:a){
        pq.emplace(r);
        while(pq.size()>k){
            pq.pop();
        }
        if(pq.size()==k){
            ans=max(ans,pq.top()-l);
        }
    }
    cout << ans << "\n";
}
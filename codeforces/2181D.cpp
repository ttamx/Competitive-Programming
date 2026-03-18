#include<bits/stdc++.h>

using namespace std;

const int L=1e9+100;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    map<int,vector<pair<int,int>>> mp;
    auto upd=[&](int l,int r,int x){
        if(l<=r){
            mp[l].emplace_back(x,r);
            if(x<L)mp[r];
        }
    };
    for(int i=0;i<n;i++){
        int k,l,r;
        cin >> k >> l >> r;
        int tot=0;
        vector<int> b(k);
        for(auto &x:b){
            cin >> x;
            tot+=x;
        }
        upd(0,l-1,L);
        upd(r+1,L,L);
        r-=tot;
        upd(l,r,l);
        for(auto &x:b){
            upd(r+1,l+x-1,L);
            l+=x,r+=x;
            upd(l,r,l);
        }
    }
    int ans=0;
    priority_queue<pair<int,int>> pq;
    pq.emplace(0,L);
    for(auto &[t,v]:mp){
        for(auto x:v)pq.emplace(x);
        while(pq.top().second<t)pq.pop();
        ans=max(ans,t-pq.top().first+1);
    }
    cout << ans << "\n";
}
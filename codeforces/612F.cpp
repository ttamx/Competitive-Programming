#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=1e18;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,s;
    cin >> n >> s;
    s--;
    map<int,vector<int>> mp;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        mp[x].emplace_back(i);
    }
    auto dist=[&](int i,int j){
        return (j-i+n)%n;
    };
    vector<pair<ll,int>> dp(n);
    dp[s].first=0;
    for(auto &[_,pos]:mp){
        vector<pair<ll,int>> aux(n);
        priority_queue<pair<pair<ll,int>,int>,vector<pair<pair<ll,int>,int>>,greater<pair<pair<ll,int>,int>>> pq;
        for(int i=0;i<n;i++)pq.emplace(aux[i]=dp[i],i);
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if(aux[u]<d)continue;
            d.first++;
            for(int dd=-1;dd<=1;dd+=2){
                int v=(u+dd+n)%n;
                if(d<aux[v])pq.emplace(aux[v]=d,v);
            }
        }
        fill(dp.begin(),dp.end(),make_pair(INF,-1));
        pos.emplace_back(pos[0]);
        {
            int idx=0;
            for(int i=0;i<n;i++){
                if(i==pos[idx])idx++;
                auto tmp=aux[pos[idx]];
                int d=dist()
                dp[i]=min(dp[i],)
            }
        }
    }

}
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m,s,t,sum,ans;
int dp[N],dp2[N];
bool vis[N];
vector<pair<int,int>> adj[N];
vector<tuple<int,int,int>> e;
multiset<pair<int,int>> ms;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> s >> t;
    e.resize(m);
    for(auto &[u,v,w]:e){
        cin >> u >> v >> w;
        sum+=w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    auto dijk=[&](int st){
        for(int i=0;i<n;i++)dp[i]=2e9,vis[i]=false;
        dp[st]=0;
        ms.emplace(0,st);
        while(!ms.empty()){
            auto [d,u]=*ms.begin();
            ms.erase(ms.begin());
            if(vis[u])continue;
            vis[u]=true;
            for(auto [v,w]:adj[u]){
                if(d+w>=dp[v])continue;
                dp[v]=d+w;
                ms.emplace(d+w,v);
            }
        }
    };
    dijk(s);
    swap(dp,dp2);
    dijk(t);
    for(auto &[u,v,w]:e)ans=max(ans,sum-min(dp[u]+dp2[v],dp[v]+dp2[u]));
    cout << ans << '\n';
}
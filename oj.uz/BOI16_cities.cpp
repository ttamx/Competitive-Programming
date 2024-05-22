#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,int>;

const int N=1e5+5;
const int K=35;
const ll INF=LLONG_MAX/2;

int n,m,k;
vector<pair<int,int>> adj[N];
ll dp[K][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> m;
    for(int mask=0;mask<1<<k;mask++)for(int i=1;i<=n;i++)dp[mask][i]=INF;
    for(int i=0;i<k;i++){
        int x;
        cin >> x;
        dp[1<<i][x]=0;
    }
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    for(int mask=1;mask<1<<k;mask++){
        for(int mask2=mask-1;mask2;mask2=mask&(mask2-1))
            for(int i=1;i<=n;i++)dp[mask][i]=min(dp[mask][i],dp[mask2][i]+dp[mask^mask2][i]);
        priority_queue<P,vector<P>,greater<P>> pq;
        for(int i=1;i<=n;i++)if(dp[mask][i]!=INF)pq.emplace(dp[mask][i],i);
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if(d>dp[mask][u])continue;
            for(auto [v,w]:adj[u])if(d+w<dp[mask][v]){
                dp[mask][v]=d+w;
                pq.emplace(d+w,v);
            }
        }
    }
    cout << *min_element(dp[(1<<k)-1]+1,dp[(1<<k)-1]+n+1);
}
#include<bits/stdc++.h>

using namespace std;

const int N=1005;
const int C=10;
const int S=1<<C;
const int MOD=1e6+3;

int n,m,k;
int c[N];
vector<int> adj[N];
int dp[S][N];
int ans=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=0;i<n;i++){
        cin >> c[i];
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=0;i<n;i++){
        dp[1<<c[i]][i]=1;
    }
    for(int mask=0;mask<(1<<k);mask++){
        for(int u=0;u<n;u++){
            if(!((mask>>c[u])&1))continue;
            for(auto v:adj[u]){
                if((mask>>c[v])&1)continue;
                int mask2=mask^(1<<c[v]);
                dp[mask2][v]=(dp[mask2][v]+dp[mask][u])%MOD;
            }
        }
    }
    for(int i=0;i<n;i++){
        ans=(ans+dp[(1<<k)-1][i])%MOD;
    }
    cout << ans << "\n";
}
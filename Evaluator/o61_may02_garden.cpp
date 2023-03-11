#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1005;
const int M=1e5+5;
const int C=(1<<10)+5;
const int MOD=1e6+3;
int n,m,c;
ll g[N],dp[N][C],p[M];
vector<int> adj[N];
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> c;
    for(int i=0;i<n;++i){
        cin >> g[i];
        g[i]=1<<g[i];
        dp[i][g[i]]=1;
    }
    for(int i=0;i<m;++i){
        int x,y;
        cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }
    for(int i=0;i<(1<<c);++i){
        for(int u=0;u<n;++u){
            if(dp[u][i]==0)continue;
            for(auto v:adj[u]){
                if(i&g[v])continue;
                int tmp=i|g[v];
                dp[v][tmp]=(dp[v][tmp]+dp[u][i])%MOD;
            }
        }
    }
    ll ans=0;
    for(int i=0;i<n;++i){
        ans=(ans+dp[i][(1<<c)-1])%MOD;
    }
    cout << ans;
}

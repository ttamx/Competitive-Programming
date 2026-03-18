#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3e5+5;
const int MOD=1e9+7;

int n,m,k;
basic_string<int> adj[N];
int disc[N],low[N];
ll pw[N],dp[N],ways[N];
int timer,comp;
vector<int> st;
ll ans;

void dfs(int u,int p){
    disc[u]=low[u]=++timer;
    st.emplace_back(u);
    for(auto v:adj[u])if(v!=p){
        if(!disc[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
        }else low[u]=min(low[u],disc[v]);
    }
    if(low[u]>disc[p]){
        int cnt=1;
        while(st.back()!=u)st.pop_back(),cnt++;
        st.pop_back();
        ans=ans*ways[cnt]%MOD;
        comp++;
    }
}

void solve(){
    cin >> n >> m >> k;
    for(int i=0,u,v;i<m;i++)cin >> u >> v,adj[u]+=v,adj[v]+=u;
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*(k-1)%MOD;
    dp[0]=dp[1]=dp[2]=1;
    dp[3]=k-1;
    ways[0]=ways[1]=1;
    for(int i=4;i<=n;i++)dp[i]=(pw[i-2]-dp[i-1]+MOD)%MOD;
    ways[2]=k-1;
    for(int i=3;i<=n;i++)ways[i]=(pw[i-1]-dp[i]+MOD)%MOD;
    ans=k;
    dfs(1,0);
    cout << ans*pw[comp-1]%MOD << "\n";
    for(int i=1;i<=n;i++)adj[i].clear(),disc[i]=low[i]=0;
    timer=comp=0;
    st.clear();
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}
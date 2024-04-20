#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,int>;

const int N=3005;
const ll INF=1e18;

int n,m,k;
vector<int> adj[N];
string s;
int a[N];
bool stop[N],good[N];
ll ds[N],dg[N];
ll dp[N][N],ans[N];
ll step[N];

void bfs(ll *dp,bool *b){
    queue<pair<int,int>> q;
    for(int i=1;i<=n;i++)dp[i]=INF;
    for(int i=1;i<=n;i++)if(b[i]){
        q.emplace(0,i);
    }
    while(!q.empty()){
        auto [d,u]=q.front();
        q.pop();
        for(auto v:adj[u])if(d+1<dp[v]){
            dp[v]=d+1;
            q.emplace(d+1,v);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    cin >> s;
    for(int i=1;i<=n;i++)stop[i]=s[i-1]=='1';
    for(int i=1;i<=k;i++)cin >> a[i];
    for(int u=1;u<=n;u++)if(stop[u]){
        for(auto v:adj[u])if(stop[v]){
            good[u]=true;
        }
    }
    bfs(ds,stop);
    bfs(dg,good);
    for(int i=2;i<=k;i++){
        int u=a[i];
        for(int t=1;t<=n;t++){
            ll val=min(ds[u]+2*t-2,dg[u]+t-1);
            step[t]+=val;
            step[t]=min(step[t],INF);
        }
    }
    for(int i=1;i<=n;i++)ans[i]=INF;
    for(int i=1;i<=n;i++)for(int j=0;j<=n;j++)dp[i][j]=INF;
    priority_queue<tuple<ll,int,int>,vector<tuple<ll,int,int>>,greater<tuple<ll,int,int>>> pq;
    pq.emplace(0,a[1],0);
    dp[a[1]][0]=ans[a[1]]=0;
    while(!pq.empty()){
        auto [d,u,t]=pq.top();
        pq.pop();
        if(d>dp[u][t])continue;
        for(auto v:adj[u]){
            ll nd=d+1,nt=t;
            ans[v]=min(ans[v],nd+step[t]);
            if(stop[v])nt++;
            if(nt<=n&&nd<dp[v][nt]){
                dp[v][nt]=nd;
                pq.emplace(nd,v,nt);
            }
        }
    }
    for(int i=1;i<=n;i++)cout << ans[i] << "\n";
}
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=50005;
const ll INF=1e12;

int n,m,k;
vector<int> adj[N];
bool stop[N],good[N];
int a[N];
ll ds[N],dg[N];
ll step[N],ans[N];
pair<ll,int> dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++){
        char c;
        cin >> c;
        if(c=='1')stop[i]=true;
    }
    for(int i=1;i<=k;i++)cin >> a[i];
    for(int u=1;u<=n;u++)if(stop[u]){
        for(auto v:adj[u])if(stop[v]){
            good[u]=true;
        }
    }
    queue<int> q;
    for(int i=1;i<=n;i++)ds[i]=INF;
    for(int u=1;u<=n;u++)if(stop[u]){
        for(auto v:adj[u])if(ds[v]==INF){
            ds[v]=1;
            q.emplace(v);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u])if(ds[v]==INF){
            ds[v]=ds[u]+1;
            q.emplace(v);
        }
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pqg;
    for(int i=1;i<=n;i++)dg[i]=INF;
    for(int u=1;u<=n;u++)if(good[u]){
        for(auto v:adj[u])if(dg[v]==INF){
            dg[v]=1;
            pqg.emplace(1,v);
        }
    }
    while(!pqg.empty()){
        auto [d,u]=pqg.top();
        pqg.pop();
        if(d>dg[u])continue;
        ll nd=dg[u]+(!good[u]);
        for(auto v:adj[u])if(nd<dg[v]){
            dg[v]=nd;
            pqg.emplace(nd,v);
        }
    }
    for(int i=2;i<=k;i++){
        int u=a[i];
        for(int j=1;j<=n;j++){
            step[j]+=min(ds[u]+(j-1)*2,dg[u]+j-1);
        }
    }
    for(int i=n;i>=2;i--)step[i]-=step[i-1];
    for(int i=1;i<=n;i++)ans[i]=INF;
    for(int i=1;i<=n;i++)dp[i]={INF,INF};
    priority_queue<tuple<ll,int,int>,vector<tuple<ll,int,int>>,greater<tuple<ll,int,int>>> pq;
    dp[a[1]]={0,0};
    ans[a[1]]=0;
    pq.emplace(0,0,a[1]);
    while(!pq.empty()){
        auto [d,t,u]=pq.top();
        pq.pop();
        if(make_pair(d,t)!=dp[u])continue;
        for(auto v:adj[u]){
            pair<ll,int> tmp(d+1,t);
            ans[v]=min(ans[v],d+1);
            if(stop[v]){
                tmp.second--;
                tmp.first+=step[-tmp.second];
            }
            if(tmp<dp[v]){
                dp[v]=tmp;
                pq.emplace(tmp.first,tmp.second,v);
            }
        }
    }
    for(int i=1;i<=n;i++)cout << ans[i] << "\n";
}
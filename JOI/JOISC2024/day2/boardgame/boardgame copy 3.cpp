#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll N=50005;
const ll INF=1e18;

ll n,m,k;
vector<ll> adj[N];
bool stop[N],good[N];
ll a[N];
ll ds[N],dg[N];
ll step[N],ans[N];
ll dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(ll i=0;i<m;i++){
        ll u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(ll i=1;i<=n;i++){
        char c;
        cin >> c;
        if(c=='1')stop[i]=true;
    }
    for(ll i=1;i<=k;i++)cin >> a[i];
    for(ll u=1;u<=n;u++)if(stop[u]){
        for(auto v:adj[u])if(stop[v]){
            good[u]=true;
        }
    }
    queue<ll> q;
    for(ll i=1;i<=n;i++)ds[i]=n+1;
    for(ll u=1;u<=n;u++)if(stop[u]){
        for(auto v:adj[u])if(ds[v]>n){
            ds[v]=1;
            q.emplace(v);
        }
    }
    while(!q.empty()){
        ll u=q.front();
        q.pop();
        for(auto v:adj[u])if(ds[v]>n){
            ds[v]=ds[u]+1;
            q.emplace(v);
        }
    }
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> ppq;
    for(ll i=1;i<=n;i++)dg[i]=n+1;
    for(ll u=1;u<=n;u++)if(good[u]){
        for(auto v:adj[u])if(dg[v]>0){
            dg[v]=0;
            ppq.emplace(0,v);
        }
    }
    while(!ppq.empty()){
        auto [d,u]=ppq.top();
        ppq.pop();
        if(d>dg[u])continue;
        if(!stop[u])d++;
        for(auto v:adj[u]){
            if(d<dg[v]){
                dg[v]=d;
                ppq.emplace(d,v);
            }
        }
    }
    for(ll i=2;i<=k;i++){
        ll u=a[i];
        if(good[u]){
            for(int j=1;j<=n;j++)step[j]++;
            continue;
        }
        ll pre=0;
        for(ll j=1;j<=n;j++){
            ll val=min(ds[u]+(j-1)*2,dg[u]+j);
            step[j]+=val-pre;
            pre=val;
        }
    }
    for(ll i=1;i<=n;i++)ans[i]=INF;
    for(int i=1;i<=n;i++)dp[i]=INF;
    ans[a[1]]=0;
    dp[a[1]]=0;
    priority_queue<tuple<ll,ll,ll>,vector<tuple<ll,ll,ll>>,greater<tuple<ll,ll,ll>>> pq;
    pq.emplace(0,0,a[1]);
    while(!pq.empty()){
        auto [d,t,u]=pq.top();
        pq.pop();
        if(d>dp[u])continue;
        for(auto v:adj[u]){
            ll nd=d+1,nt=t;
            ans[v]=min(ans[v],nd);
            if(stop[v]){
                nd+=step[++nt];
            }
            if(nd<dp[v]){
                dp[v]=nd;
                pq.emplace(nd,nt,v);
            }
        }
    }
    for(ll i=1;i<=n;i++)cout << ans[i] << "\n";
}
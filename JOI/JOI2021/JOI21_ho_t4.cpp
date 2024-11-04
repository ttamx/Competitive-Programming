#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=100'005;
const int M=200'005;
const ll INF=LLONG_MAX/2;

int n,m;
int eu[M],ev[M],ec[M],ew[M];
vector<pair<int,int>> adj[N];
map<int,vector<pair<int,int>>> adjc[N];
map<int,ll> sum[N];
map<int,array<ll,2>> dp[N];
bool vis[N];
map<int,bool> vis2[N];
priority_queue<tuple<ll,int,int,int>,vector<tuple<ll,int,int,int>>,greater<tuple<ll,int,int,int>>> pq;
ll ans=INF;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        cin >> eu[i] >> ev[i] >> ec[i] >> ew[i];
        adj[eu[i]].emplace_back(ev[i],i);
        adj[ev[i]].emplace_back(eu[i],i);
        adjc[eu[i]][ec[i]].emplace_back(ev[i],i);
        adjc[ev[i]][ec[i]].emplace_back(eu[i],i);
        dp[eu[i]][i]={INF,INF};
        dp[ev[i]][i]={INF,INF};
    }
    for(int u=1;u<=n;u++){
        for(auto [v,i]:adj[u]){
            sum[u][ec[i]]+=ew[i];
        }
    }
    for(auto [v,i]:adj[1]){
        dp[v][i][0]=min(sum[1][ec[i]]-ew[i],(ll)ew[i]);
        dp[v][i][1]=ew[i];
        pq.emplace(dp[v][i][0],v,i,0);
        pq.emplace(dp[v][i][1]-ew[i],v,i,1);
    }
    while(!pq.empty()){
        auto [d,u,i,t]=pq.top();
        pq.pop();
        if(u==n){
            ans=min(ans,d+(t?ew[i]:0));
            continue;
        }
        if(!t&&!vis[u]){
            vis[u]=true;
            for(auto [v,j]:adj[u]){
                if(i==j)continue;
                ll d1=d+ew[j];
                ll d0=min(d+sum[u][ec[j]]-ew[j],d1);
                if(d0<dp[v][j][0]){
                    dp[v][j][0]=d0;
                    pq.emplace(d0,v,j,0);
                }
                if(d1<dp[v][j][1]){
                    dp[v][j][1]=d1;
                    pq.emplace(d1-ew[j],v,j,1);
                }
            }
        }
        if(t&&!vis2[u][ec[i]]){
            vis2[u][ec[i]]=true;
            for(auto [v,j]:adjc[u][ec[i]]){
                if(i==j)continue;
                ll d0=d+sum[u][ec[j]]-ew[j];
                ll d1=d+ew[j]+ew[i];
                if(d0<dp[v][j][0]){
                    dp[v][j][0]=d0;
                    pq.emplace(d0,v,j,0);
                }
                if(d1<dp[v][j][1]){
                    dp[v][j][1]=d1;
                    pq.emplace(d1-ew[j],v,j,1);
                }
            }
        }
    }
    cout << (ans<INF?ans:-1LL);
}
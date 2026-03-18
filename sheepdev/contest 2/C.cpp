#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int n,k,lg;

struct Tree{
    vector<vector<pair<int,int>>> adj;
    vector<ll> dist;
    vector<int> disc;
    vector<vector<pair<int,int>>> st;
    int timer;
    void init(){
        adj.assign(n,{});
        dist.assign(n,0LL);
        disc.assign(n,0);
        st.assign(lg+1,vector<pair<int,int>>(n*2));
        for(int i=0;i<n-1;i++){
            int u,v,w;
            cin >> u >> v >> w;
            u--,v--;
            adj[u].emplace_back(v,w);
            adj[v].emplace_back(u,w);
        }
        timer=-1;
        dfs(0,-1,0);
        for(int i=1;i<=lg;i++){
            int len=1<<i;
            for(int j=0;j+2*len<=2*n;j++){
                st[i][j]=min(st[i-1][j],st[i-1][j+len]);
            }
        }
    }
    void dfs(int u,int p,int d){
        disc[u]=++timer;
        st[0][timer]={d,u};
        for(auto [v,w]:adj[u])if(v!=p){
            dist[v]=dist[u]+w;
            dfs(v,u,d+1);
            st[0][++timer]={d,u};
        }
    }
    ll calc(int u,int v){
        auto [l,r]=minmax(disc[u],disc[v]);
        int k=31-__builtin_clz(r-l+1);
        int x=min(st[k][l],st[k][r-(1<<k)+1]).second;
        return dist[u]+dist[v]-2*dist[x];
    }
}tr[5];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> k >> n >> lg;
    while((1<<lg)<=n)lg++;
    for(int i=0;i<k;i++)tr[i].init();
    tuple<ll,int,int> ans(0,0,0);
    for(int u=0;u<n;u++){
        for(int v=u+1;v<n;v++){
            ll res=0;
            for(int i=0;i<k;i++){
                res+=tr[i].calc(u,v);
            }
            ans=min(ans,make_tuple(res,u,v));
        }
    }
    auto [x,u,v]=ans;
    cout << u+1 << " " << v+1 << " " << x << "\n";
}
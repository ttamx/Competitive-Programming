#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=505;
const int NN=N*N;
const int K=70;
const ll INF=1e18;
const int M=1<<22;

int n,m,k;
char a[N][N];
int d[K][NN];
vector<int> adj[NN];
vector<pair<int,int>> edges;
bool used[K];
int id[NN];
int buf=0;
int st,cnt=0;
ll ans=0;
vector<int> sources;
ll c[K][K];
ll dp[M];

inline int enc(int i,int j){
    return (i-1)*m+(j-1);
}

void bfs(int s){
    int i=id[s];
    queue<int> q;
    for(int u=0;u<n*m;u++){
        d[i][u]=-1;
    }
    d[i][s]=0;
    q.emplace(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u]){
            if(d[i][v]==-1){
                d[i][v]=d[i][u]+1;
                q.emplace(v);
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]=='S'){
                st=enc(i,j);
                sources.emplace_back(st);
            }
            if(i+1<=n&&a[i][j]!='#'&&a[i+1][j]!='#'){
                edges.emplace_back(enc(i,j),enc(i+1,j));
            }
            if(j+1<=m&&a[i][j]!='#'&&a[i][j+1]!='#'){
                edges.emplace_back(enc(i,j),enc(i,j+1));
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]=='X'){
                id[enc(i,j)]=++buf;
                sources.emplace_back(enc(i,j));
            }
        }
    }
    for(auto [u,v]:edges){
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=0;i<=k;i++){
        bfs(sources[i]);
    }
    for(auto u:sources){
        if(d[0][u]==-1){
            cout << -1 << "\n";
            exit(0);
        }
        ans+=d[0][u];
    }
    for(int i=1;i<=k;i++){
        for(int j=1;j<=k;j++){
            c[i-1][j-1]=d[i][sources[j]];
        }
        c[i-1][i-1]=d[0][sources[i]];
    }
    for(int mask=0;mask<(1<<k);mask++){
        dp[mask]=INF;
    }
    dp[0]=0;
    for(int mask=0;mask<(1<<k);mask++){
        for(int i=0;i<k;i++){
            if(mask>>i&1)continue;
            for(int j=i;j<k;j++){
                if(mask>>j&1)continue;
                int mask2=mask|(1<<i)|(1<<j);
                dp[mask2]=min(dp[mask2],dp[mask]+c[i][j]);
            }
        }
    }
    cout << ans+dp[(1<<k)-1] << "\n";
}
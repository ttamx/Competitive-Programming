#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int N=5005;

int n;
vector<int> adj[N];
pair<int,int> du[N];
int ord[N];
bool vis[N];
mint pw[N];

struct Fenwick{
    int t[N];
    void init(){
        for(int i=1;i<=n;i++){
            t[i]=0;
        }
    }
    void update(int i,int v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

void bfs_u(int st){
    queue<pair<int,int>> q;
    q.emplace(0,st);
    vis[st]=true;
    int idx=0;
    while(!q.empty()){
        auto [d,u]=q.front();
        q.pop();
        du[++idx]={d,u};
        for(auto v:adj[u]){
            if(!vis[v]){
                vis[v]=true;
                q.emplace(d+1,v);
            }
        }
    }
    for(int i=1;i<=n;i++){
        vis[i]=false;
    }
}

void bfs_v(int st){
    queue<pair<int,int>> q;
    q.emplace(0,st);
    vis[st]=true;
    int idx=0;
    while(!q.empty()){
        auto [d,u]=q.front();
        q.pop();
        ord[u]=++idx;
        for(auto v:adj[u]){
            if(!vis[v]){
                vis[v]=true;
                q.emplace(d+1,v);
            }
        }
    }
    for(int i=1;i<=n;i++){
        vis[i]=false;
    }
}

void runcase(){
    cin >> n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++){
        sort(adj[i].begin(),adj[i].end());
    }
    mint ans=0;
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=pw[i-1]*2;
    }
    for(int u=1;u<=n;u++){
        bfs_u(u);
        for(auto v:adj[u]){
            bfs_v(v);
            f.init();
            int cnt=0;
            for(int i=1;i<=n;i++){
                auto [d,x]=du[i];
                int p=ord[x];
                f.update(p,+1);
                cnt++;
                int used=f.query(p);
                mint ways=(pw[p-used]-mint(1))*pw[n-p-(cnt-used)];
                ans+=ways*d*2+ways;
            }
        }
    }
    cout << ans/2 << "\n";
    for(int i=1;i<=n;i++){
        adj[i].clear();
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
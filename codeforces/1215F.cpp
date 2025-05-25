#include<bits/stdc++.h>

using namespace std;

const int N=400005;
const int M=400000*4+5;

int n,p,f,m;
int pre[N],suf[N];
vector<int> adj[M],rev[M];
vector<int> ord;
int scc[M],scc_id;
bool vis[M];
int timer;

inline void add_edge(int u,int v){
    adj[u].emplace_back(v);
    rev[v].emplace_back(u);
}
inline void add_clause(int u,bool su,int v,bool sv){
    u=u<<1|su,v=v<<1|sv;
    add_edge(u^1,v);
    add_edge(v^1,u);
}
inline bool get(int u){return scc[u<<1]<scc[u<<1|1];}

void dfs(int u){
    if(vis[u])return;
    vis[u]=true;
    for(auto v:adj[u])dfs(v);
    ord.emplace_back(u);
}

void dfs2(int u){
    if(scc[u])return;
    scc[u]=scc_id;
    for(auto v:rev[u])dfs2(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> p >> f >> m;
    for(int i=1;i<=n;i++){
        int u,v;
        cin >> u >> v;
        add_clause(u,1,v,1);
    }
    for(int i=1;i<=p;i++){
        int l,r;
        cin >> l >> r;
        add_clause(i,0,p+l,1);
        if(r<f)add_clause(i,0,p+r+1,0);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        add_clause(u,0,v,0);
    }
    for(int i=2;i<=f;i++)add_clause(p+i-1,1,p+i,0);
    for(int i=2;i<=(p+f)*2+1;i++)dfs(i);
    reverse(ord.begin(),ord.end());
    for(auto u:ord)if(!scc[u]){
        scc_id++;
        dfs2(u);
    }
    for(int i=1;i<=p+f;i++)if(scc[i*2]==scc[i*2+1]){
        cout << -1 << "\n";
        exit(0);
    }
    vector<int> ans;
    int ff=0;
    for(int i=1;i<=p;i++)if(get(i))ans.emplace_back(i);
    for(int i=1;i<=f;i++)if(get(p+i))ff=i;
    assert(ff);
    cout << ans.size() << " " << ff << "\n";
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}
#include<bits/stdc++.h>

using namespace std;

const int INF=1e9;

struct Dinic{
    struct Edge{
        int to,flow,cap;
        int rem(){return cap-flow;}
    };
    int n,s,t;
    vector<Edge> e;
    vector<vector<int>> g;
    vector<int> ptr,lv;
    Dinic(int n,int s,int t):n(n),s(s),t(t),g(n){}
    void add_edge(int u,int v,int cap){
        g[u].emplace_back(e.size());
        e.emplace_back(Edge{v,0,cap});
        g[v].emplace_back(e.size());
        e.emplace_back(Edge{u,0,0});
    }
    bool bfs(){
        lv.assign(n,-1);
        queue<int> q;
        q.emplace(s);
        lv[s]=0;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int j:g[u]){
                int v=e[j].to;
                if(lv[v]==-1&&e[j].rem()>0){
                    q.emplace(v);
                    lv[v]=lv[u]+1;
                }
            }
        }
        return lv[t]!=-1;
    }
    int dfs(int u,int f){
        if(u==t||!f)return f;
        for(int &i=ptr[u];i<g[u].size();i++){
            int j=g[u][i];
            int v=e[j].to;
            if(lv[v]==lv[u]+1){
                int res=dfs(v,min(f,e[j].rem()));
                if(res>0){
                    e[j].flow+=res;
                    e[j^1].flow-=res;
                    return res;
                }
            }
        }
        return 0;
    }
    int max_flow(){
        int res=0;
        while(bfs()){
            ptr.assign(n,0);
            while(true){
                int f=dfs(s,INF);
                if(!f)break;
                res+=f;
            }
        }
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> col(n,-1);
    function<void(int)> dfs=[&](int u){
        for(auto v:adj[u])if(col[v]==-1){
            col[v]=col[u]^1;
            dfs(v);
        }
    };
    for(int i=0;i<n;i++)if(col[i]==-1){
        col[i]=0;
        dfs(i);
    }
    Dinic mf(n+2,n,n+1);
    for(int i=0;i<n;i++){
        if(col[i]){
            mf.add_edge(mf.s,i,a[i]);
            for(auto j:adj[i])mf.add_edge(i,j,INF);
        }else{
            mf.add_edge(i,mf.t,a[i]);
        }
    }
    cout << accumulate(a.begin(),a.end(),0)-mf.max_flow() << "\n";
}
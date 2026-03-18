#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=305;

struct HopcroftKarp{
    int n,m;
    vector<int> match,lv,ptr;
    vector<vector<int>> adj;
    HopcroftKarp(int _n,int _m):n(_n),m(_m),adj(n){}
    void add_edge(int u,int v){
        adj[u].emplace_back(v+n);
    }
    void bfs(){
        lv.assign(n,-1);
        queue<int> q;
        for(int i=0;i<n;i++)if(match[i]==-1){
            lv[i]=0;
            q.emplace(i);
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto v:adj[u])if(match[v]!=-1&&lv[match[v]]==-1){
                lv[match[v]]=lv[u]+1;
                q.emplace(match[v]);
            }
        }
    }
    bool dfs(int u){
        for(int &i=ptr[u];i<adj[u].size();i++){
            int v=adj[u][i];
            if(match[v]==-1||(lv[match[v]]==lv[u]+1&&dfs(match[v]))){
                match[u]=v,match[v]=u;
                return true;
            }
        }
        return false;
    }
    int solve(){
        int ans=0,cnt=0;
        match.assign(n+m,-1);
        do{
            ptr.assign(n,0);
            bfs();
            cnt=0;
            for(int i=0;i<n;i++)if(match[i]==-1&&dfs(i))cnt++;
            ans+=cnt;
        }while(cnt);
        return ans;
    }
};

struct DSU{
    vector<int> fa;
    DSU(int n):fa(n){
        iota(fa.begin(),fa.end(),0);
    }
    int fp(int u){
        return fa[u]=u==fa[u]?u:fp(fa[u]);
    }
    bool uni(int u,int v){
        u=fp(u),v=fp(v);
        return u!=v?fa[u]=v,true:false;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<tuple<int,int,int>> edges(m),mst;
    for(auto &[w,u,v]:edges){
        cin >> u >> v >> w;
        u--,v--;
    }
    vector<vector<int>> a(k);
    for(auto &v:a){
        int s;
        cin >> s;
        v.resize(s);
        for(auto &x:v){
            cin >> x;
            x--;
        }
    }
    sort(edges.begin(),edges.end());
    DSU dsu(n);
    int ans=0;
    for(auto [w,u,v]:edges){
        if(dsu.uni(u,v)){
            mst.emplace_back(w,u,v);
            ans+=w;
        }
    }
    if(mst.size()<n-1){
        cout << -1 << "\n";
        exit(0);
    }
    int comp=1;
    vector<bool> del(n-1);
    for(int i=mst.size()-1;i>=0;i--){
        DSU dsu(n);
        for(int j=0;j<mst.size();j++){
            if(j!=i&&!del[j]){
                auto [w,u,v]=mst[j];
                dsu.uni(u,v);
            }
        }
        HopcroftKarp bm(k,n);
        for(int j=0;j<k;j++){
            for(auto u:a[j]){
                bm.add_edge(j,dsu.fp(u));
            }
        }
        if(bm.solve()==comp+1){
            ans-=get<0>(mst[i]);
            del[i]=true;
            comp++;
        }
    }
    cout << (comp==k?ans:-1) << "\n";
}
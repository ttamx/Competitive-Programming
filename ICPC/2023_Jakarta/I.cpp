#include<bits/stdc++.h>

using namespace std;

struct HopcroftKarp{
    int n,m;
    vector<int> l,r,lv,ptr;
    vector<vector<int>> g;
    HopcroftKarp(){}
    HopcroftKarp(int _n,int _m){init(_n,_m);}
    void init(int _n,int _m){
        n=_n,m=_m;
        g.assign(n,vector<int>());
    }
    void add_edge(int u,int v){
        g[u].emplace_back(v+n);
    }
    void bfs(){
        lv.assign(n,-1);
        queue<int> q;
        for(int i=0;i<n;i++){
            if(l[i]==-1){
                lv[i]=0;
                q.emplace(i);
            }
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int x:g[u]){
                int v=r[x];
                if(v!=-1&&lv[v]==-1){
                    lv[v]=lv[u]+1;
                    q.emplace(v);
                }
            }
        }
    }
    bool dfs(int u){
        for(int &i=ptr[u];i<(int)g[u].size();i++){
            int x=g[u][i],v=r[x];
            if(v==-1||(lv[v]==lv[u]+1&&dfs(v))){
                l[u]=x;
                r[x]=u;
                return true;
            }
        }
        return false;
    }
    int max_matching(){
        int res=0;
        l.assign(n+m,-1);
        r.assign(n+m,-1);
        while(true){
            ptr.assign(n,0);
            bfs();
            int cnt=0;
            for(int i=0;i<n;i++){
                if(l[i]==-1&&dfs(i)){
                    cnt++;
                }
            }
            res+=cnt;
            if(cnt==0){
                break;
            }
        }
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    HopcroftKarp mbm(n,n);
    vector<pair<int,int>> edges(n-1);
    for(auto &[u,v]:edges){
        cin >> u >> v;
        u--,v--;
        mbm.add_edge(u,v);
    }
    mbm.max_matching();
    vector<int> nxt(n,-1),pre(n,-1);
    for(int i=0;i<n;i++){
        if(mbm.l[i]!=-1){
            nxt[i]=mbm.l[i]-n;
            pre[nxt[i]]=i;
        }
    }
    vector<vector<int>> path;
    vector<int> id(n);
    for(int i=0;i<n;i++){
        if(pre[i]==-1){
            vector<int> res;
            for(int u=i;u!=-1;u=nxt[u]){
                res.emplace_back(u);
                id[u]=path.size();
            }
            path.emplace_back(res);
        }
    }
    int m=path.size();
    vector<vector<int>> g(m);
    vector<int> deg(m);
    for(auto [u,v]:edges){
        if(id[u]!=id[v]){
            g[id[u]].emplace_back(id[v]);
            deg[id[v]]++;
        }
    }
    vector<int> q;
    for(int i=0;i<m;i++){
        if(deg[i]==0){
            q.emplace_back(i);
        }
    }
    for(int i=0;i<(int)q.size();i++){
        int u=q[i];
        for(auto v:g[u]){
            deg[v]--;
            if(deg[v]==0){
                q.emplace_back(v);
            }
        }
    }
    cout << (int)q.size()-1 << "\n";
    for(int i=1;i<(int)q.size();i++){
        cout << path[q[i-1]].back()+1 << " " << path[q[i]][0]+1 << "\n";
    }
}
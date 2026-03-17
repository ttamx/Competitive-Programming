#include<bits/stdc++.h>

using namespace std;

struct HopcroftKarp{
    int n,m;
    vector<int> match,lv,ptr;
    vector<vector<int>> adj;
    HopcroftKarp(){}
    HopcroftKarp(int _n,int _m){init(_n,_m);}
    void init(int _n,int _m){
        n=_n,m=_m;
        adj.assign(n+m,vector<int>{});
    }
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
            for(int v:adj[u])if(match[v]!=-1&&lv[match[v]]==-1){
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
    int max_matching(){
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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int>> e(m);
    for(auto &[w,u,v]:e){
        cin >> u >> v >> w;
        u--,v--;
    }
    sort(e.begin(),e.end());
    int l=0,r=m;
    while(l<r){
        int mid=(l+r)/2;
        HopcroftKarp mbm(n,n);
        for(int i=0;i<=mid;i++){
            auto [w,u,v]=e[i];
            mbm.add_edge(u,v);
        }
        if(mbm.max_matching()==n)r=mid;
        else l=mid+1;
    }
    cout << (l<m?get<0>(e[l]):-1) << "\n";
}
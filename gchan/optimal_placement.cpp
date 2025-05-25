#include<bits/stdc++.h>

using namespace std;

struct TwoSAT{
    int n;
    vector<vector<int>> adj,rev;
    TwoSAT(int _n):n(_n),adj(n*2),rev(n*2){}
    void add_edge(int u,int v){
        adj[u].emplace_back(v);
        rev[v].emplace_back(u);
    }
    void add_clause(int u,bool nu,int v,bool nv){
        u=(u<<1)|nu,v=(v<<1)|nv;
        add_edge(u^1,v);
        add_edge(v^1,u);
    }
    pair<bool,vector<bool>> solve(){
        vector<bool> vis(n*2),ans(n);
        vector<int> ord,scc(n*2);
        int scc_id=0;
        function<void(int)> dfs=[&](int u){
            if(vis[u])return;
            vis[u]=true;
            for(auto v:adj[u])dfs(v);
            ord.emplace_back(u);
        };
        function<void(int)> dfs2=[&](int u){
            if(scc[u])return;
            scc[u]=scc_id;
            for(auto v:rev[u])dfs2(v);
        };
        for(int i=0;i<2*n;i++)dfs(i);
        reverse(ord.begin(),ord.end());
        for(int i:ord)if(!scc[i]){
            scc_id++;
            dfs2(i);
        }
        for(int i=0;i<n;i++){
            if(scc[i<<1]==scc[(i<<1)|1])return {false,ans};
            ans[i]=scc[i<<1]>scc[(i<<1)|1];
        }
        return {true,ans};
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<array<pair<int,int>,2>> a(m),b(m);
    for(int i=0;i<m;i++)for(int j=0;j<2;j++)cin >> a[i][j].first >> a[i][j].second;
    int l=0,r=n*2;
    auto work=[&](int mid){
        TwoSAT sat(m);
        for(int i=0;i<m;i++)for(int ii=0;ii<2;ii++)for(int j=0;j<i;j++)for(int jj=0;jj<2;jj++){
            int dx=a[i][ii].first-a[j][jj].first,dy=a[i][ii].second-a[j][jj].second;
            if(abs(dx)+abs(dy)<mid)sat.add_clause(i,ii,j,jj);
        }
        return sat.solve();
    };
    while(l<r){
        int mid=(l+r+1)/2;
        if(work(mid).first)l=mid;
        else r=mid-1;
    }
    cout << l << "\n";
    auto ans=work(l).second;
    for(auto x:ans)cout << "AB"[x];
}
#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;

int n,m;
pair<int,int> edge[N];
vector<pair<int,int>> adj[N];
int pa[N],pid[N],lv[N];
int fa[N];
int ans[N];
bool ok[N];

int fp(int u){
    return fa[u]=u==fa[u]?u:fp(fa[u]);
}

void dfs(int u,int p=0){
    lv[u]=lv[p]+1;
    for(auto [v,i]:adj[u])if(v!=p){
        pa[v]=u;
        pid[v]=i;
        dfs(v,u);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        auto &[u,v]=edge[i];
        cin >> u >> v;
    }
    for(int i=1;i<n;i++){
        int x;
        cin >> x;
        auto [u,v]=edge[x];
        adj[u].emplace_back(v,x);
        adj[v].emplace_back(u,x);
        ok[x]=true;
    }
    dfs(1);
    for(int i=1;i<=n;i++)fa[i]=i;
    int cnt=1;
    for(int i=1;i<=m;i++){
        if(ans[i])continue;
        auto [u,v]=edge[i];
        u=fp(u),v=fp(v);
        vector<int> res;
        while(u!=v){
            if(lv[u]<lv[v])swap(u,v);
            res.emplace_back(pid[u]);
            u=fa[u]=fp(pa[u]);
        }
        sort(res.begin(),res.end());
        for(auto j:res)ans[j]=cnt++;
        if(!ok[i])ans[i]=cnt++;
    }
    for(int i=1;i<=m;i++)cout << ans[i] << " ";
}
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;

int n,m;
int col[N],lv[N],pa[N][20];
ll sum[N];
set<int> s[N];
vector<pair<int,int>> adj[N];
multiset<ll,greater<ll>> ans,ms[N];

void dfs(int u,int p){
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto [v,c]:adj[u]){
        if(v==p)continue;
        col[v]=c;
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(lv[a]<lv[b])swap(a,b);
    for(int i=19;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
    if(a==b)return a;
    for(int i=19;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
    return pa[a][0];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<n;i++){
        int u,v,w,c;
        cin >> u >> v >> w >> c;
        adj[u].emplace_back(v,c);
        adj[v].emplace_back(u,c);
        sum[c]+=w;
        if(!s[c].insert(u).second)s[c].erase(u);
        if(!s[c].insert(v).second)s[c].erase(v);
    }
    for(int i=1;i<=n;i++)ms[i].insert(0);
    for(int i=1;i<=n;i++){
        if(s[i].size()==2){
            int u=*s[i].begin(),v=*s[i].rbegin();
            ms[lca(u,v)].insert(sum[i]);
        }
    }

} 
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m,p; 
int val[N],val2[N];
char ans[N];
vector<pair<int,int>> adj[N];
bool vis[N],used[N];

void dfs(int u,int p){
    vis[u]=true;
    for(auto [v,i]:adj[u]){
        if(used[abs(i)])continue;
        used[abs(i)]=true;
        if(!vis[v]){
            dfs(v,i);
            if(val2[v]>0||val[v]==0)ans[abs(i)]='B';
            else ans[abs(i)]=((val[v]<0)^(i>0))?'L':'R';
            val[u]+=val[v];
            val2[u]+=val2[v];
        }else{
            ans[abs(i)]='B';
            val2[u]++;
            val2[v]--;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,-i);
    }
    cin >> p;
    for(int i=1;i<=p;i++){
        int u,v;
        cin >> u >> v;
        val[u]++;
        val[v]--;
    }
    for(int i=1;i<=n;i++)if(!vis[i])dfs(i,0);
    for(int i=1;i<=m;i++)cout << ans[i];
}
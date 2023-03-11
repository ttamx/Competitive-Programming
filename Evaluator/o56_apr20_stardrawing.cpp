#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m;
vector<int> adj[N];
unordered_map<int,bool> cyc;
set<vector<int>> s;
set<pair<int,int>> s1,s2;
bool vis[N];
bool chk;

int dfs(int u,int p,int r){
    if(vis[u])return 0;
    vis[u]=true;
    int ret=1;
    for(auto v:adj[u]){
        if(v==p)continue;
        if(v==r){
            cyc[r]=true;
            continue;
        }
        ret+=dfs(v,u,r);
    }
    return ret;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;++i){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;++i){
        if(adj[i].size()==3){
            vis[i]=true;
            vector<int> tmp;
            int loop=0,lin=0;
            for(auto v:adj[i]){
                if(vis[v])continue;
                if(cyc[i]){
                    lin=dfs(v,i,i);
                    continue;
                }
                int sz=dfs(v,i,i);
                if(cyc[i])loop=sz;
                else tmp.emplace_back(sz);
            }
            if(tmp.size()==3){
                sort(tmp.begin(),tmp.end());
                s.insert(tmp);
            }else{
                s1.insert({lin,loop});
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(vis[i])continue;
        int sz=dfs(i,0,i);
        s2.insert({cyc[i],sz});
    }
    cout << s.size()+s1.size()+s2.size();
}
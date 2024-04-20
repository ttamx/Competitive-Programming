#include<bits/stdc++.h>

using namespace std;

const int N=30;
const int M=300;

int n,m;
vector<pair<int,int>> adj[N];
bool used[M];
int idx[N];

void dfs(int u){
    for(;idx[u]<adj[u].size();idx[u]++){
        auto [v,i]=adj[u][idx[u]];
        if(!used[i]){
            used[i]=true;
            dfs(v);
        }
    }
    cout << char(u+'A') << " ";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        char u,v;
        cin >> u >> v;
        u-='A',v-='A';
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
        m=max({m,int(u),int(v)});
    }
    int st=0;
    for(int i=0;i<=m;i++){
        if(adj[i].size()%2){
            st=i;
        }
    }
    dfs(st);
}
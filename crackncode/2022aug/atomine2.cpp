#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
vector<int> adj[N];
int in[N],out[N];
int t;

struct fenwick{
    int t[N];
    void add(int i,int v){
        while(i<N)t[i]^=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i>0)res^=t[i],i-=i&-i;
        return res;
    }
}f;

void dfs(int u,int p){
    in[u]=++t;
    for(auto v:adj[u])if(v!=p)dfs(v,u);
    out[u]=t;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,0);
    while(q--){
        int x,y;
        cin >> x >> y;
        if(x==1)f.add(in[y],1),f.add(out[y]+1,1);
        else cout << f.read(in[y]) << '\n';
    }
}
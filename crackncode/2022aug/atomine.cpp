#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
int p[N],a[N],t[N];
vector<int> adj[N],c[N];

void add(int i,int v){
    t[i]*=v;
    for(auto u:c[i])add(u,v);
}

int read(int i){
    int ret=1;
    while(i>0){
        ret*=t[i];
        i=p[i];
    }
    return ret;
}

void dfs(int u,int d,int l){
    a[d]=u;
    p[u]=a[d-(d&-d)];
    for(int i=0;d-(1<<i)>d-(d&-d);++i){
        c[a[d-(1<<i)]].emplace_back(u);
    }
    for(auto v:adj[u]){
        if(v==l)continue;
        dfs(v,d+1,u);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;++i)t[i]=1;
    for(int i=1;i<n;++i){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,1,0);
    while(q--){
        int z,x;
        cin >> z >> x;
        if(z==1)add(x,-1);
        if(z==2)cout << (read(x)==-1) << '\n';
    }
}

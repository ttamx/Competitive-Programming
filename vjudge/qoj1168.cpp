#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=30;

int n,m,q;
vector<pair<int,int>> adj[N];
int d[N],basis[K];
bool vis[N];
int qs[N];

void insert(int x){
    for(int i=K-1;i>=0;i--)if(x>>i&1){
        if(!basis[i])return void(basis[i]=x);
        x^=basis[i];
    }
}

void compress(){
    for(int i=K-1;i>=0;i--)if(basis[i]){
        for(int j=i-1;j>=0;j--)if(basis[j]){
            if(basis[i]>>j&1)basis[i]^=basis[j];
        }
    }
}

void dfs(int u){
    vis[u]=true;
    for(auto [v,w]:adj[u]){
        if(!vis[v])d[v]=d[u]^w,dfs(v);
        else insert(d[u]^d[v]^w);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    dfs(1);
    compress();
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]^d[i];
    while(q--){
        int l,r;
        cin >> l >> r;
        int sz=r-l+1,t=(1ll*sz*(sz-1)/2)&1,sum=qs[r]^qs[l-1];
        if(sz&1)sum=0;
        int ans=sum;
        for(int i=K-1;i>=0;i--)if(sum>>i&1^t)ans^=basis[i];
        cout << ans << "\n";
    }
}
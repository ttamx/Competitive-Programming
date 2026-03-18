#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n,m;
int a[N];
vector<pair<int,int>> adj[N];
int deg[N],ans[N];
bool vis[N];
int fa[N];

int fp(int u){
    return fa[u]=u==fa[u]?u:fp(fa[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=n+1;i>=1;i--){
        a[i]^=a[i-1];
    }
    for(int i=1;i<=n+1;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int l,r;
        cin >> l >> r;
        r++;
        if(fp(l)==fp(r))continue;
        fa[fp(l)]=fp(r);
        adj[l].emplace_back(r,i);
        adj[r].emplace_back(l,i);
        deg[l]++;
        deg[r]++;
    }
    queue<int> q;
    for(int i=1;i<=n+1;i++){
        if(deg[i]==1){
            q.emplace(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=true;
        for(auto [v,i]:adj[u]){
            if(vis[v])continue;
            ans[i]=a[u];
            a[u]^=ans[i];
            a[v]^=ans[i];
            if(--deg[v]==1){
                q.emplace(v);
            }
        }
    }
    for(int i=1;i<=n+1;i++){
        if(a[i]){
            cout << -1 << "\n";
            exit(0);
        }
    }
    cout << m << "\n";
    for(int i=1;i<=m;i++){
        cout << i << " " << ans[i] << "\n";
    }
}
#include<bits/stdc++.h>

using namespace std;

const int N=3005;

int n,k,q;
int a[N],p[N],vis[N];
vector<int> adj[N];

bool dfs(int u){
    if(vis[u])return vis[u]==1;
    vis[u]=1;
    for(auto v:adj[u])if(dfs(v))return true;
    vis[u]=2;
    return false;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++){
        int l=i,r=n;
        while(l<r){
            int m=(l+r+1)/2;
            bool b=false;
            for(int j=i;j<m;j++){
                if(b)adj[a[j]].emplace_back(a[j+1]);
                else adj[a[j+1]].emplace_back(a[j]);
                b^=true;
            }
            bool ok=true;
            for(int j=i;j<=m;j++)if(dfs(a[j])){
                ok=false;
                break;
            }
            for(int j=i;j<=m;j++){
                adj[a[j]].clear();
                vis[a[j]]=0;
            }
            if(ok)l=m;
            else r=m-1;
        }
        p[i]=l;
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        cout << (p[l]>=r?"YES":"NO") << "\n";
    }
}
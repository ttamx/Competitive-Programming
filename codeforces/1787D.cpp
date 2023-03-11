#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+2);
    vector<vector<int>> adj(n+2);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        if(a[i]+i>=1&&a[i]+i<=n)adj[a[i]+i].push_back(i);
    }
    vector<int> vis(n+2),ok(n+2);
    function<int(int)> dfs=[&](int u){
        if(u<1||u>n)return 1;
        if(vis[u])return ok[u];
        vis[u]=true;
        return ok[u]=dfs(u+a[u]);
    };
    for(int i=1;i<=n;i++)dfs(i);
    long long cnt=0;
    for(int i=1;i<=n;i++)cnt+=ok[i];
    long long ans=0;
    int u=1;
    vis=vector<int>(n+2,0);
    vector<int> vis2=vis;
    bool plus=false;
    if(ok[1])plus=true;
    function<void(int)> dfs2=[&](int u){
        if(vis2[u])return;
        vis2[u]=true;
        if(ok[u]){
            ok[u]=false;
            cnt--;
        }
        for(auto v:adj[u])dfs2(v);
    };
    while(u>=1&&u<=n&&!vis[u]){
        vis[u]=true;
        dfs2(u);
        ans+=n+1;
        ans+=cnt;
        u+=a[u];
    }
    if(plus){
        for(int i=1;i<=n;i++)if(!vis[i])ans+=2*n+1;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
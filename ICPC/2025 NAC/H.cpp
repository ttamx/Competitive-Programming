#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<ll> l(n),r(n),mn(n),mx(n);
    function<void(int,int)> dfs=[&](int u,int p){
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            mn[u]+=l[v];
            mx[u]+=r[v];
        }
        r[u]=k-mn[u];
        if(a[u]!=-1){
            l[u]=max(l[u],a[u]);
            r[u]=min(r[u],a[u]);
        }
        if(l[u]>r[u]){
            cout << "-1\n";
            exit(0);
        }
    };
    dfs(0,-1);
    ll ans=0;
    function<ll(int,int)> dfs2=[&](int u,int p){
        ans+=l[u];
        ll cur=l[u],add=0;
        for(auto v:adj[u]){
            if(v==p)continue;
            add+=dfs2(v,u);
            cur+=l[v];
        }
        cur=k-cur;
        assert(cur>=0);
        add=min(add,cur);
        ans+=add;
        return min(cur-add,r[u]-l[u]);
    };
    ll d=dfs2(0,-1);
    cout << ans+d << "\n";
}
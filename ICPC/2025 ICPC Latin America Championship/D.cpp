#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> d(n);
    for(auto &x:d)cin >> x;
    vector<tuple<int,int,int>> edges(m);
    for(auto &[w,u,v]:edges){
        cin >> u >> v;
        u--,v--;
        w=max(d[u],d[v]);
    }
    sort(edges.begin(),edges.end());
    vector<int> fa(2*n-1),par(2*n-1,-1),sz(2*n-1,1);
    vector<ll> a(2*n-1);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u){
        return fa[u]=u==fa[u]?u:fp(fa[u]);
    };
    int cur=n;
    for(auto [w,u,v]:edges){
        u=fp(u),v=fp(v);
        if(u==v)continue;
        sz[cur]=sz[u]+sz[v];
        a[u]+=1LL*sz[v]*w;
        a[v]+=1LL*sz[u]*w;
        fa[u]=fa[v]=par[u]=par[v]=cur++;
    }
    for(int i=2*n-3;i>=0;i--){
        a[i]+=a[par[i]];
    }
    for(int i=0;i<n;i++){
        cout << a[i]+d[i] << " \n"[i==n-1];
    }
}
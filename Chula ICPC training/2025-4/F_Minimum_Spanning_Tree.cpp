#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int>> edges(m);
    for(auto &[w,u,v]:edges){
        cin >> u >> v >> w;
        u--,v--;
    }
    vector<int> fa(n);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u){
        return u==fa[u]?u:fa[u]=fp(fa[u]);
    };
    long long ans=0;
    sort(edges.begin(),edges.end());
    for(auto [w,u,v]:edges){
        u=fp(u),v=fp(v);
        if(u!=v){
            ans+=w;
            fa[v]=u;
        }
    }
    cout << ans << "\n";
}
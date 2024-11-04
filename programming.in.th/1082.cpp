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
    sort(edges.begin(),edges.end());
    vector<int> p(n);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        return p[u]=u==p[u]?u:fp(p[u]);
    };
    auto uni=[&](int u,int v){
        u=fp(u),v=fp(v);
        return u!=v?p[u]=v,true:false;
    };
    for(auto [w,u,v]:edges){
        if(uni(u,v)){
            cout << u+1 << " " << v+1 << "\n";
        }
    }
}
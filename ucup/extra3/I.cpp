#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,m,q;
    cin >> n >> m >> q;
    vector<ll> a(n),c(n);
    for(auto &x:a)cin >> x;
    for(auto &x:c)cin >> x;
    vector<tuple<ll,int,int>> edges(m);
    for(auto [w,u,v]:edges)cin >> u >> v >> w,u--,v--;
    vector<int> fa(2*n-1),par(2*n-1);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u){
        return u==fa[u]?u:fp(fa[u]);
    };
    sort(edges.begin(),edges.end());
    int buf=n;
    a.resize(2*n-1);
    c.resize(2*n-1);
    vector<ll> w(2*n-1);
    for(auto [ww,u,v]:edges){
        u=fp(u),v=fp(v);
        if(u==v)continue;
        fa[u]=fa[v]=par[u]=par[v]=buf;
        w[u]=w[v]=ww;
        a[buf]=a[u]+a[v];
        c[buf]=min(c[u],c[v]);
        buf++;
    }
    int lg=0;
    while((1<<lg)<n)lg++;
    vector<vector<int>> jump(lg,vector<int>(n));
    jump[0]=par;
    jump[0][2*n-1]=2*n-1;
    for(int i=0;i+1<lg;i++){
        for(int u=0;u<2*n-1;u++){
            jump[i+1][u]=jump[i][jump[i][u]];
        }
    }
    for(int i=2*n-2;i>=0;i--){

    }
    vector<ll> to(2*n-1),rem(2*n-1);
    for(int u=0;u<2*n-1;u++){

    }
}

int main(){
    int t;
    cin >> t;
    while(t--)runcase();
}
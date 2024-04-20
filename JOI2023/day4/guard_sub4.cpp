#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

using ll = long long;

int n,m,q;
int s[N],deg[N];
ll ans;
vector<tuple<ll,int,int>> edge;
int p[N];

int fp(int u){
    return p[u]=u==p[u]?u:fp(p[u]);
}

bool uni(int u,int v){
    u=fp(u),v=fp(v);
    return u!=v?p[u]=v,true:false;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++){
        cin >> s[i];
        ans-=s[i];
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        edge.emplace_back(s[u]+s[v],u,v);
    }
    ans+=*max_element(s+1,s+n+1);
    sort(edge.begin(),edge.end());
    for(int i=1;i<=n;i++)p[i]=i;
    for(auto [w,u,v]:edge)if(uni(u,v))ans+=w;
    cout << ans;
}
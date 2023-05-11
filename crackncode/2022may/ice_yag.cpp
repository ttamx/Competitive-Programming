#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m,s,e,ans=200;
int fa[N];
vector<pair<int,int>> edge[205];

int fp(int u){
    if(u==fa[u])return u;
    return fa[u]=fp(fa[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> s >> e;
    for(int i=0;i<m;i++){
        int u,v,t;
        cin >> u >> v >> t;
        edge[t].emplace_back(u,v);
    }
    for(int i=1;i<=200;i++){
        int j=i;
        iota(fa,fa+n+1,0);
        while(j<=200&&fp(s)!=fp(e)){
            for(auto [u,v]:edge[j]){
                u=fp(u),v=fp(v);
                if(u==v)continue;
                fa[u]=v;
            }
            j++;
        }
        if(fp(s)!=fp(e))break;
        ans=min(ans,j-i-1);
    }
    cout << ans;
}
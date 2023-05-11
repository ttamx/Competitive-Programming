#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=40005;
const int mod=1e9+7;

int n,m;
int fa[N];
ll ans,cnt=1;
map<int,vector<pair<int,int>>> edge;

int fp(int u){
    if(u==fa[u])return u;
    return fa[u]=fp(fa[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    iota(fa,fa+n+1,0);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        edge[w].emplace_back(u,v);
    }
    for(auto [w,v]:edge){
        vector<pair<int,int>> e;
        for(auto [u,v]:v){
            u=fp(u),v=fp(v);
            if(u!=v){
                if(u>v)swap(u,v);
                e.emplace_back(u,v);
            }
        }
        if(e.empty())continue;
        bool ok=false;
        for(auto [u,v]:e){
            u=fp(u),v=fp(v);
            if(u!=v){
                fa[u]=v;
                ans+=w;
            }else{
                ok=true;
            }
        }
        if(e.size()==2){
            if(e[0]==e[1]){
                cnt*=2;
                cnt%=mod;
            }
        }else if(e.size()==3){
            sort(e.begin(),e.end());
            if(e[0]==e[2]){
                cnt*=3;
                cnt%=mod;
            }else if(e[0]==e[1]||e[1]==e[2]){
                cnt*=2;
                cnt%=mod;
            }else if(ok){
                cnt*=3;
                cnt%=mod;
            }
        }
    }
    cout << ans << " " << cnt;
}
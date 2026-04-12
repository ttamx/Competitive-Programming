#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int B=60;
const int N=1e5+5;

struct XORBasis{
    ll basis[B];
    int rank=0;
    void init(){
        for(int i=0;i<B;i++){
            basis[i]=0;
        }
        rank=0;
    }
    bool insert(ll x){
        for(int i=B-1;i>=0;i--)if(x>>i&1){
            if(!basis[i]){
                basis[i]=x;
                rank++;
                return true;
            }
            x^=basis[i];
        }
        return false;
    }
}bs;

int n,m;
vector<pair<int,ll>> adj[N];
ll dist[N];
bool vis[N];
mint pw[B+1];
mint cnt[B][2];
int num;

void dfs(int u){
    num++;
    for(int i=0;i<B;i++){
        cnt[i][dist[u]>>i&1]++;
    }
    vis[u]=true;
    for(auto [v,w]:adj[u]){
        if(!vis[v]){
            dist[v]=dist[u]^w;
            dfs(v);
        }else{
            bs.insert(dist[u]^dist[v]^w);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v;
        ll w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    pw[0]=1;
    for(int i=1;i<=B;i++)pw[i]=pw[i-1]*2;
    mint ans=0;
    for(int i=1;i<=n;i++)if(!vis[i]){
        bs.init();
        for(int j=0;j<B;j++){
            cnt[j][0]=cnt[j][1]=0;
        }
        num=0;
        dfs(i);
        mint ways=mint(1LL*num*(num-1)/2);
        ll mask=0;
        for(int j=0;j<B;j++){
            mask|=bs.basis[j];
        }
        for(int j=0;j<B;j++){
            if(mask>>j&1){
                ans+=pw[j]*ways*pw[bs.rank-1];
            }else{
                ans+=pw[j]*cnt[j][0]*cnt[j][1]*pw[bs.rank];
            }
        }
    }
    cout << ans << "\n";
}
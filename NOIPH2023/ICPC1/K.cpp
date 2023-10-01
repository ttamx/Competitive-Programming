#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;
typedef tuple<int,int,int> t3;

const int N=1e5+5;
const int M=2e5+5;
const int Q=3e5+5;

int n,m,q;
t3 edge[M];
bool closed[M];
int dp[N];
vector<pair<int,int>> adj[N];
t3 qr[Q];
int pa[N];
vector<int> com[N];

struct gauss{
    array<int,30> base;
    void add(int x){
        for(int i=29;i>=0;i--){
            if((x>>i)&1){
                if(base[i]){
                    x^=base[i];
                }else{
                    base[i]=x;
                    return;
                }
            }
        }
    }
}gs[N];

int fp(int u){
    if(u==pa[u])return u;
    return pa[u]=fp(pa[u]);
}

void add(int idx){
    auto [u,v,w]=edge[idx];
    int pu=fp(u),pv=fp(v);
    if(pu==pv){
        gs[pu].add(dp[u]^dp[v]^w);
    }else{
        if(com[pu].size()<com[pv].size()){
            swap(u,v);
            swap(pu,pv);
        }
        for(auto x:com[pv]){
            dp[x]^=dp[u]^dp[v]^w;
            com[pu].emplace_back(x);
        }
        for(int i=0;i<30;i++)gs[pu].add(gs[pv].base[i]);
        com[pv].clear();
        pa[pv]=pu;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        auto &[u,v,w]=edge[i];
        cin >> u >> v >> w;
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        auto &[t,x,y]=qr[i];
        char c;
        cin >> c;
        t=c=='?';
        if(t==0){
            cin >> x;
            closed[x]=true;
        }else{
            cin >> x >> y;
        }
    }
    for(int i=1;i<=n;i++){
        pa[i]=i;
        com[i].emplace_back(i);
    }
    for(int i=1;i<=m;i++){
        if(!closed[i]){
            add(i);
        }
    }
    vector<int> ans;
    for(int i=q;i>=1;i--){
        auto [t,x,y]=qr[i];
        if(t==0){
            add(x);
        }else{
            int res=-1;
            int px=fp(x),py=fp(y);
            if(px==py){
                res=dp[x]^dp[y];
                for(int j=29;j>=0;j--){
                    res=min(res,res^gs[px].base[j]);
                }
            }
            ans.emplace_back(res);
        }
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans){
        if(x==-1)cout << "DIJKSTRAPPED\n";
        else cout << x << "\n";
    }
}
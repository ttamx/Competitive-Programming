#include<bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF=INT_MAX/2;

struct DSU{
    int n;
    vector<int> fa,wt,sz,prio;
    DSU(int n):n(n),fa(n),wt(n),sz(n),prio(n){
        for(int i=0;i<n;i++){
            fa[i]=i;
            wt[i]=INF;
            sz[i]=1;
            prio[i]=rng();
        }
    }
    int find(int u,int w=INF-1){
        while(wt[u]<=w){
            while(wt[fa[u]]<=wt[u]){
                sz[fa[u]]-=sz[u];
                fa[u]=fa[fa[u]];
            }
            u=fa[u];
        }
        return u;
    }
    
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);

}
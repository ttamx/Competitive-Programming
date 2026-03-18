#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int INF=INT_MAX/2;

mt19937 rng(time(0));

int n,m;

struct DSU{
    int fa[N],wt[N],id[N],prio[N];
    void init(){
        for(int i=0;i<n;i++){
            fa[i]=i;
            wt[i]=INF;
            id[i]=-1;
            prio[i]=rng();
        }
    }
    int find(int u,int w=INF-1){
        while(wt[u]<=w){
            while(wt[fa[u]]<=wt[u])fa[u]=fa[fa[u]];
            u=fa[u];
        }
        return u;
    }
    int get_max(int u,int v){
        if(find(u)!=find(v))return -1;
        while(fa[u]!=v&&fa[v]!=u){
            if(wt[u]<wt[v])u=fa[u];
            else v=fa[v];
        }
        return fa[u]==v?u:v;
    }
    void _add_edge(int u,int v,int w,int i){
        while(u!=v){
            u=find(u,w),v=find(v,w);
            if(prio[u]<prio[v])swap(u,v);
            swap(wt[v],w);
            swap(id[v],i);
            swap(fa[v],u);
        }
    }
    int add_edge(int u,int v,int w,int i){
        if(u==v)return i;
        int p=get_max(u,v);
        if(p==-1){
            _add_edge(u,v,w,i);
            return -1;
        }
        if(wt[p]>w){
            int x=id[p];
            fa[p]=p;
            wt[p]=INF;
            id[p]=-1;
            _add_edge(u,v,w,i);
            return x;
        }
        return i;
    }
}dsu;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    dsu.init();
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        cout << dsu.add_edge(u,v,w,i) << " \n"[i==m-1];
    }
}
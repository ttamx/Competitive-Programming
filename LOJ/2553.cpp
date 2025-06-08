#include<bits/stdc++.h>

using namespace std;

const int N=366670;

int n;

struct Tree{
    vector<pair<int,int>> adj[N];
    void read(){
        for(int i=0;i<n-1;i++){
            int u,v;
            cin >> u >> v;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
    }
}t1,t2;

struct StaticTopTree{
    using P = pair<int,int>;
    enum Type{COMPRESS,RAKE,ADD_EDGE,ADD_VERTEX,VERTEX};
    struct Node{
        int l,r,p;
        Type t;
    }node[2*N];
    int hv[N];
    int buf;
    int dfs(int u,int p){
        int s=1,mx=0;
        for(auto [v,w]:t1.adj[u]){
            int t=dfs(v,u);
            if(t>mx)t=mx,hv[u]=v;
            s+=t;
        }
        return s;
    }
    int add(int i,int l,int r,Type t){
        if(!i)i=++buf;
        node[i]=Node{l,r,0,t};
        if(l)node[l].p=i;
        if(r)node[r].p=i;
    }
    P merge(vector<P> a,Type t){
        if(a.size()==1)return a[0];
        int tot=0;
        vector<P> b,c;
        for(auto [i,s]:a)tot+=s;
        for(auto [i,s]:a)(tot>s?b:c).emplace_back(i,s),tot-=s*2;
        auto [i,si]=merge(b,t);
        auto [j,sj]=merge(c,t);
        return {add(0,i,j,t),si+sj};
    }
    P compress(int i){
        vector<P> a{add_vertex(i)};  
    }
    P rake(int i){

    }
    P add_edge(int i){
        
    }
    P add_vertex(int i){
        
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
}
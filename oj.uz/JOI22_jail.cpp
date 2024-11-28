#include<bits/stdc++.h>

using namespace std;

const int N=120005;

int n,m;
vector<int> adj[N];

struct PathUp{
    struct Node;
    using Ptr = Node*;
    struct Node{
        set<int> a;
        Ptr par;
        Node(int u):a{u},par(this){}
    };
    Ptr head;
    PathUp():head(){}
    PathUp(int u):head(new Node(u)){}
    Ptr find_root(Ptr u){
        if(u->par)return u->par=find_root(u->par);
        return u;
    }
    void merge(Ptr u,Ptr v){
        u=find_root(u),v=find_root(v);
        assert(find_root(u)!=find_root(v));
        if(u->a.size()<v->a.size()){
            swap(u->a,v->a);
        }
        for(auto x:v->a){
            u->a.emplace(x);
        }
        v->a.clear();
        v->par=u;
    }
};

void runcase(){
    cin >> n;
    for(int i=0;i<n-1;i++){ 
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    cin >> m;
    for(int i=1;i<=m;i++){
        
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}
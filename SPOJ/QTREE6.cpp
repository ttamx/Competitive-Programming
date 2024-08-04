#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
int a[N];
vector<int> adj[N];

struct StaticTopTree{
    enum Type{Compress,Rake,AddEdge,AddVertex,Vertex};
    int pa[N],hv[N];
    int lch[4*N],rch[4*N],par[4*N];
    Type type[N];
    int node_id,root;
    int dfs(int u,int p){
        pa[u]=p;
        int s=1,mx=0;
        for(auto v:adj[u])if(v!=p){
            int t=dfs(v,u);
            s+=t;
            if(t>mx)mx=t,hv[u]=v;
        }
        return s;
    }
    int add(int i,int l,int r,Type t){
        if(!i)i=++node_id;
        par[i]=0,lch[i]=l,rch[i]=r,type[i]=t;
        if(l)par[l]=i;
        if(r)par[r]=i;
        return i;
    }
    pair<int,int> merge(const vector<pair<int,int>> &a,Type t){
        if(a.size()==1)return a[0];
        vector<pair<int,int>> b,c;
        int tot=0;
        for(auto &[i,s]:a)tot+=s;
        for(auto &[i,s]:a){
            (tot>s?b:c).emplace_back(i,s);
            tot-=s*2;
        }
        auto [i,si]=merge(b,t);
        auto [j,sj]=merge(c,t);
        return {add(0,i,j,t),si+sj};
    }
    pair<int,int> compress(int i){
        vector<pair<int,int>> a{add_vertex(i)};
        while(hv[i])a.emplace_back(add_vertex(i=hv[i]));
        return merge(a,Type::Compress);
    }
    pair<int,int> rake(int i){
        vector<pair<int,int>> a;
        for(auto j:adj[i])if(j!=pa[i]&&j!=hv[i])a.emplace_back(add_edge(j));
        return a.empty()?make_pair(0,0):merge(a,Type::Rake);
    }
    pair<int,int> add_edge(int i){
        auto [j,s]=compress(i);
        return {add(0,j,0,Type::AddEdge),s};
    }
    pair<int,int> add_vertex(int i){
        auto [j,s]=rake(i);
        return {add(i,j,0,j?Type::AddVertex:Type::Vertex),s+1};
    }
    void build(){
        node_id=n;
        dfs(1,0);
        root=compress(1).first;
    }
}stt;

struct TreeDP{
    struct Point{
        array<int,2> cnt;
        Point():cnt(){}
    }point[4*N];
    struct Path{
        array<int,2> cnt,pcnt;
        int psum;
        Path():cnt(),pcnt(),psum(0){}
    }path[4*N];
    Path compress(Path p,Path c){
        Path res=p;
        for(int i=0;i<2;i++)if(p.pcnt[i]==p.psum)res.cnt[i]+=c.cnt[i];
        for(int i=0;i<2;i++)res.pcnt[i]+=c.pcnt[i];
        res.psum+=c.psum;
        return res;
    }
    Point rake(Point l,Point r){
        Point res;
        for(int i=0;i<2;i++)res.cnt[i]=l.cnt[i]+r.cnt[i];
        return res;
    }
    Point add_edge(Path d){
        Point res;
        for(int i=0;i<2;i++)res.cnt[i]=d.cnt[i];
        return res;
    }
    Path add_vertex(Point d,int i){
        Path res;
        res.cnt[a[i]]=1+d.cnt[a[i]];
        res.pcnt[a[i]]=res.psum=1;
        return res;
    }
    Path vertex(int i){
        Path res;
        res.cnt[a[i]]=res.pcnt[a[i]]=res.psum=1;
        return res;
    }
    void _update(int i){
        if(stt.type[i]==stt.Type::Compress){
            path[i]=compress(path[stt.lch[i]],path[stt.rch[i]]);
        }else if(stt.type[i]==stt.Type::Rake){
            point[i]=rake(point[stt.lch[i]],point[stt.rch[i]]);
        }else if(stt.type[i]==stt.Type::AddEdge){
            point[i]=add_edge(path[stt.lch[i]]);
        }else if(stt.type[i]==stt.Type::AddVertex){
            path[i]=add_vertex(point[stt.lch[i]],i);
        }else{
            path[i]=vertex(i);
        }
    }
    void dfs(int i){
        if(!i)return;
        dfs(stt.lch[i]);
        dfs(stt.rch[i]);
        _update(i);
    }
    void build(){
        dfs(stt.root);
    }
    void update(int i){
        for(;i;i=stt.par[i])_update(i);
    }
    Path get_subtree(int i){
        Path res=path[i];
        while(true){
            int p=stt.par[i];
            if(!p||stt.type[p]!=stt.Type::Compress)break;
            if(stt.lch[p]==i)res=compress(res,path[stt.rch[p]]);
            i=p;
        }
        return res;
    }
}dp;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    stt.build();
    dp.build();
    cin >> q;
    while(q--){
        int t,u;
        cin >> t >> u;
        if(t){
            a[u]^=1;
            dp.update(u);
        }else{
            cout << dp.get_subtree(u).cnt[a[u]] << "\n";
        }
    }
}
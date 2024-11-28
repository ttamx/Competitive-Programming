#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
int a[N];
vector<int> adj[N];

struct StaticTopTree{
    using P = pair<int,int>;
    enum Type{Compress,Rake,AddEdge,AddVertex,Vertex};
    int pa[N],hv[N];
    int lch[4*N],rch[4*N],par[4*N];
    Type type[N];
    int node_id,root;
    int dfs(int u){
        int s=1,mx=0;
        for(auto v:adj[u])if(v!=pa[u]){
            pa[v]=u;
            int t=dfs(v);
            s+=t;
            if(t>mx)mx=t,hv[u]=v;
        }
        return s;
    }
    int add(int i,int l,int r,Type t){
        if(!i)i=++node_id;
        lch[i]=l,rch[i]=r,type[i]=t;
        if(l)par[l]=i;
        if(r)par[r]=i;
        return i;
    }
    
    P compress(int i){
        vector<P> a{add_vertex(i)};
        auto work=[&](){
            auto [sj,j]=a.back();
            a.pop_back();
            auto [si,i]=a.back();
            a.back()={max(si,sj)+1,add(0,i,j,Compress)};
        };
        while(hv[i]!=0){
            a.emplace_back(add_vertex(i=hv[i]));
            while(true){
                if(a.size()>=3&&(a.end()[-3].first==a.end()[-2].first||a.end()[-3].first<=a.back().first)){
                    P tmp=a.back();
                    a.pop_back();
                    work();
                    a.emplace_back(tmp);
                }else if(a.size()>=2&&a.end()[-2].first<=a.back().first){
                    work();
                }else break;
            }
        }
        while(a.size()>=2)work();
        return a[0];
    }
    P rake(int i){
        priority_queue<P,vector<P>,greater<P>> pq;
        for(int j:adj[i])if(j!=pa[i]&&j!=hv[i])pq.emplace(add_edge(j));
        while(pq.size()>=2){
            auto [si,i]=pq.top();pq.pop();
            auto [sj,j]=pq.top();pq.pop();
            pq.emplace(max(si,sj)+1,add(0,i,j,Rake));
        }
        return pq.empty()?make_pair(0,0):pq.top();
    }
    P add_edge(int i){
        auto [sj,j]=compress(i);
        return {sj+1,add(0,j,0,AddEdge)};
    }
    P add_vertex(int i){
        auto [sj,j]=rake(i);
        return {sj+1,add(i,j,0,j?AddVertex:Vertex)};
    }
    void build(){
        node_id=n;
        dfs(1);
        root=compress(1).second;
    }
}stt;

struct TreeDP{
    struct Path{
        int c0,c1;
        bool p0,p1;
        static Path unit(){
            return {0,0,1,1};
        }
    }path[4*N],rpath[4*N];
    struct Point{
        int c0,c1;
        static Point unit(){
            return {0,0};
        }
    }point[4*N];
    Path compress(Path l,Path r){
        return {l.c0+(l.p0?r.c0:0),l.c1+(l.p1?r.c1:0),l.p0&&r.p0,l.p1&&r.p1};
    }
    Point rake(Point l,Point r){
        return {l.c0+r.c0,l.c1+r.c1};
    }
    Point add_edge(Path p){
        return {p.c0,p.c1};
    }
    Path add_vertex(Point p,int u){
        return {a[u]==0?p.c0+1:0,a[u]==1?p.c1+1:0,a[u]^1,a[u]};
    }
    Path vertex(int u){
        return {a[u]^1,a[u],a[u]^1,a[u]};
    }
    void build(){
        dfs(stt.root);
    }
    void _update(int u){
        if(stt.type[u]==stt.Compress){
            path[u]=compress(path[stt.lch[u]],path[stt.rch[u]]);
            rpath[u]=compress(rpath[stt.rch[u]],rpath[stt.lch[u]]);
        }else if(stt.type[u]==stt.Rake){
            point[u]=rake(point[stt.lch[u]],point[stt.rch[u]]);
        }else if(stt.type[u]==stt.AddEdge){
            point[u]=add_edge(path[stt.lch[u]]);
        }else if(stt.type[u]==stt.AddVertex){
            path[u]=rpath[u]=add_vertex(point[stt.lch[u]],u);
        }else{
            path[u]=rpath[u]=vertex(u);
        }
    }
    void dfs(int u){
        if(!u)return;
        dfs(stt.lch[u]);
        dfs(stt.rch[u]);
        _update(u);
    }
    void update(int u){
        while(u){
            _update(u);
            u=stt.par[u];
        }
    }
    Path query_all(){
        return path[stt.root];
    }
    Path query_reroot(int r){
        int u=r;
        Point res;
        vector<tuple<Path,Path,Point,int>> a;
        while(true){
            int p=stt.par[u];
            Path below=Path::unit(),above=Path::unit();
            while(p&&stt.type[p]==stt.Compress){
                int l=stt.lch[p],r=stt.rch[p];
                if(l==u){
                    below=compress(below,path[r]);
                }else{
                    above=compress(above,rpath[l]);
                }
                u=p;
                p=stt.par[u];
            }
            if(p){
                u=p;
                p=stt.par[u];
                Point sum=Point::unit();
                while(stt.type[p]==stt.Rake){
                    int l=stt.lch[p],r=stt.rch[p];
                    sum=rake(sum,u==r?point[l]:point[r]);
                    u=p;
                    p=stt.par[u];
                }
                u=p;
                a.emplace_back(below,above,sum,u);
            }else{
                res=rake(add_edge(below),add_edge(above));
                break;
            }
        }
        reverse(a.begin(),a.end());
        for(auto &[below,above,sum,u]:a){
            sum=rake(sum,res);
            above=compress(above,add_vertex(sum,u));
            res=rake(add_edge(below),add_edge(above));
        }
        if(stt.type[r]==stt.AddVertex){
            res=rake(res,point[stt.lch[r]]);
        }
        return add_vertex(res,r);
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
            auto res=dp.query_reroot(u);
            cout << (a[u]?res.c1:res.c0) << "\n";
        }
    }
}
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int M=2e5+5;
const ll INF=1e18;

int n,q;
int a[M],w[M];
vector<int> adj[M];
int cnt;
map<pair<int,int>,int> id;

struct StaticTopTree{
    using P = pair<int,int>;
    enum Type{Compress,Rake,AddEdge,AddVertex,Vertex};
    int root,cur_node;
    int hv[M],p[M];
    int lch[4*M],rch[4*M],par[4*M];
    Type type[4*M];
    int dfs(int u){
        int s=1,mx=0;
        for(auto v:adj[u]){
            if(v!=p[u]){
                p[v]=u;
                int t=dfs(v);
                s+=t;
                if(t>mx){
                    mx=t;
                    hv[u]=v;
                }
            }
        }
        return s;
    }
    void build(int _root){
        cur_node=2*n-1;
        dfs(_root);
        root=compress(_root).second;
    }
    int add(int i,int l,int r,Type t){
        if(!i)i=++cur_node;
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
        while(hv[i]){
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
        for(int j:adj[i])if(j!=p[i]&&j!=hv[i])pq.emplace(add_edge(j));
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
}stt;

struct Info{ll ans,sum;} dp[4*M],rdp[4*M];

Info compress(const Info &l,const Info &r){return {min(l.ans,l.sum+r.ans),l.sum+r.sum};}
Info rake(const Info &l,const Info &r){return {min(l.ans,r.ans),0LL};}
Info add_edge(const Info &p){return p;}
Info add_vertex(const Info &p,int u){return a[u]?Info{w[u],w[u]}:Info{p.ans+w[u],w[u]};}
Info vertex(int u){return a[u]?Info{0LL,0LL}:Info{INF,w[u]};}

void pull(int u){
    if(stt.type[u]==stt.Vertex){
        dp[u]=rdp[u]=vertex(u);
    }else if(stt.type[u]==stt.Compress){
        dp[u]=compress(dp[stt.lch[u]],dp[stt.rch[u]]);
        rdp[u]=compress(rdp[stt.rch[u]],rdp[stt.lch[u]]);
    }else if(stt.type[u]==stt.Rake){
        dp[u]=rake(dp[stt.lch[u]],dp[stt.rch[u]]);
    }else if(stt.type[u]==stt.AddEdge){
        dp[u]=add_edge(dp[stt.lch[u]]);
    }else{
        dp[u]=rdp[u]=add_vertex(dp[stt.lch[u]],u);
    }
}

void update(int u){
    for(;u;u=stt.par[u])pull(u);
}

void dfs(int u){
    if(!u)return;
    dfs(stt.lch[u]);
    dfs(stt.rch[u]);
    pull(u);
}

Info rec(int u){
    int p=stt.par[u];
    Info below=Info{INF,0LL},above=Info{INF,0LL};
    while(p&&stt.type[p]==stt.Compress){
        int l=stt.lch[p],r=stt.rch[p];
        if(l==u)below=compress(below,dp[r]);
        else above=compress(above,rdp[l]);
        u=p;
        p=stt.par[u];
    }
    if(p){
        u=p;
        p=stt.par[u];
        Info sum=Info{INF,0LL};
        while(stt.type[p]==stt.Rake){
            int l=stt.lch[p],r=stt.rch[p];
            sum=rake(sum,u==r?dp[l]:dp[r]);
            u=p;
            p=stt.par[u];
        }
        sum=rake(sum,rec(p));
        above=compress(above,add_vertex(sum,p));
    }
    return rake(add_edge(below),add_edge(above));
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v >> w[i+n];
        if(u>v)swap(u,v);
        id[{u,v}]=i+n;
        adj[u].emplace_back(i+n);
        adj[v].emplace_back(i+n);
        adj[i+n].emplace_back(u);
        adj[i+n].emplace_back(v);
    }
    stt.build(1);
    dfs(stt.root);
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int u;
            cin >> u;
            if(cnt==0){
                cout << -1 << "\n";
            }else{
                Info res=rec(u);
                if(stt.type[u]==stt.AddVertex){
                    res=rake(res,dp[stt.lch[u]]);
                }
                cout << add_vertex(res,u).ans << "\n";
            }
        }else if(op==2){
            int u;
            cin >> u;
            cnt-=a[u];
            a[u]^=1;
            cnt+=a[u];
            update(u);
        }else if(op==3){
            int u,v,ww;
            cin >> u >> v >> ww;
            if(u>v)swap(u,v);
            int i=id[{u,v}];
            w[i]=ww;
            update(i);
        }else{
            assert(false);
        }
    }
}
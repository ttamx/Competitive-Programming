#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

template<class T,bool directed=true,bool scaling=true>
struct Dinic{
    struct Edge{
        int to;
        T flow,cap;
        Edge(int _to,T _cap):to(_to),flow(0),cap(_cap){}
        T remain(){return cap-flow;}
    };
    int n,s,t;
    T U;
    vector<Edge> e;
    vector<vector<int>> g;
    vector<int> ptr,lv;
    bool calculated;
    T max_flow;
    Dinic(){}
    Dinic(int n,int s,int t){init(n,s,t);}
    void init(int _n,int _s,int _t){
        n=_n,s=_s,t=_t;
        U=0;
        e.clear();
        g.assign(n,{});
        calculated=false;
    }
    void add_edge(int from,int to,T cap){
        assert(0<=from&&from<n&&0<=to&&to<n);
        g[from].emplace_back(e.size());
        e.emplace_back(to,cap);
        g[to].emplace_back(e.size());
        e.emplace_back(from,directed?0:cap);
        U=max(U,cap);
    }
    bool bfs(T scale){
        lv.assign(n,-1);
        vector<int> q{s};
        lv[s]=0;
        for(int i=0;i<(int)q.size();i++){
            int u=q[i];
            for(int j:g[u]){
                int v=e[j].to;
                if(lv[v]==-1&&e[j].remain()>=scale){
                    q.emplace_back(v);
                    lv[v]=lv[u]+1;
                }
            }
        }
        return lv[t]!=-1;
    }
    T dfs(int u,int t,T f){
        if(u==t||f==0)return f;
        for(int &i=ptr[u];i<(int)g[u].size();i++){
            int j=g[u][i];
            int v=e[j].to;
            if(lv[v]==lv[u]+1){
                T res=dfs(v,t,min(f,e[j].remain()));
                if(res>0){
                    e[j].flow+=res;
                    e[j^1].flow-=res;
                    return res;
                }
            }
        }
        return 0;
    }
    T flow(){
        if(calculated)return max_flow;
        calculated=true;
        max_flow=0;
        for(T scale=scaling?1LL<<(63-__builtin_clzll(U)):1LL;scale>0;scale>>=1){
            while(bfs(scale)){
                ptr.assign(n,0);
                while(true){
                    T f=dfs(s,t,INF);
                    if(f==0)break;
                    max_flow+=f;
                }
            }
        }
        return max_flow;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,d;
    while(cin >> n >> m >> d){
        vector<string> a(n);
        for(auto &x:a){
            cin >> x;
        }
        Dinic<int> mf(n*m*2+2,n*m*2,n*m*2+1);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                int u=i*m+j;
                if(a[i][j]=='@'){
                    mf.add_edge(u*2,u*2+1,INF);
                }else if(a[i][j]=='.'){
                    mf.add_edge(u*2,u*2+1,1);
                }else if(a[i][j]=='*'){
                    mf.add_edge(u*2,u*2+1,1);
                    mf.add_edge(mf.s,u*2,INF);
                }else if(a[i][j]=='#'){
                    mf.add_edge(u*2,u*2+1,INF);
                    mf.add_edge(u*2+1,mf.t,d);
                }
                if(i>0){
                    int v=(i-1)*m+j;
                    mf.add_edge(u*2+1,v*2,INF);
                    mf.add_edge(v*2+1,u*2,INF);
                }
                if(j>0){
                    int v=i*m+j-1;
                    mf.add_edge(u*2+1,v*2,INF);
                    mf.add_edge(v*2+1,u*2,INF);
                }
            }
        }
        cout << mf.flow() << "\n";
    }
}
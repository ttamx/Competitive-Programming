#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

struct Dinic{
    struct Edge{
        int to,flow,cap;
        Edge(int _to,int _cap):to(_to),flow(0),cap(_cap){}
        int remain(){return cap-flow;}
    };
    int n,s,t;
    int U;
    vector<Edge> e;
    vector<vector<int>> g;
    vector<int> ptr,lv;
    Dinic(){}
    Dinic(int n,int s,int t){init(n,s,t);}
    void init(int _n,int _s,int _t){
        n=_n,s=_s,t=_t;
        U=0;
        e.clear();
        g.assign(n,{});
    }
    void add_edge(int from,int to,int cap){
        g[from].emplace_back(e.size());
        e.emplace_back(to,cap);
        g[to].emplace_back(e.size());
        e.emplace_back(from,0);
        U=max(U,cap);
    }
    bool bfs(int scale){
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
    int dfs(int u,int t,int f){
        if(u==t||f==0)return f;
        for(int &i=ptr[u];i<(int)g[u].size();i++){
            int j=g[u][i];
            int v=e[j].to;
            if(lv[v]==lv[u]+1){
                int res=dfs(v,t,min(f,e[j].remain()));
                if(res>0){
                    e[j].flow+=res;
                    e[j^1].flow-=res;
                    return res;
                }
            }
        }
        return 0;
    }
    int flow(){
        int max_flow=0;
        for(int scale=1<<(31-__builtin_clzll(U));scale>0;scale>>=1){
            while(bfs(scale)){
                ptr.assign(n,0);
                while(true){
                    int f=dfs(s,t,INF);
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
    int n;
    cin >> n;
    int m=n*n+2*n;
    Dinic mf(m+2,m,m+1);
    int cnt=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int x;
            cin >> x;
            int u=i*n+j;
            if(x>1){
                x--;
                mf.add_edge(mf.s,u,x);
                mf.add_edge(u,n*n+i,x);
                mf.add_edge(u,n*n+n+j,x);
            }else if(x==0){
                mf.add_edge(n*n+i,u,1);
                mf.add_edge(n*n+n+j,u,1);
                mf.add_edge(u,mf.t,1);
                cnt++;
            }
        }
    }
    cout << cnt*2-mf.flow() << "\n";
}
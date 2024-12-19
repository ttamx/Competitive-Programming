#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

struct HopcroftKarp{
    int n,m;
    vi l,r,lv,ptr;
    vector<vi> adj;
    HopcroftKarp(){}
    HopcroftKarp(int _n,int _m){init(_n,_m);}
    void init(int _n,int _m){
        n=_n,m=_m;
        adj.assign(n+m,vi{});
    }
    void addEdge(int u,int v){
        adj[u].emplace_back(v+n);
    }
    void bfs(){
        lv=vi(n,-1);
        queue<int> q;
        for(int i=0;i<n;i++)if(l[i]==-1){
            lv[i]=0;
            q.emplace(i);
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int v:adj[u])if(r[v]!=-1&&lv[r[v]]==-1){
                lv[r[v]]=lv[u]+1;
                q.emplace(r[v]);
            }
        }
    }
    bool dfs(int u){
        for(int &i=ptr[u];i<adj[u].size();i++){
            int v=adj[u][i];
            if(r[v]==-1||(lv[r[v]]==lv[u]+1&&dfs(r[v]))){
                l[u]=v,r[v]=u;
                return true;
            }
        }
        return false;
    }
    int maxMatching(){
        int match=0,cnt=0;
        l=r=vi(n+m,-1);
        do{
            ptr=vi(n);
            bfs();
            cnt=0;
            for(int i=0;i<n;i++)if(l[i]==-1&&dfs(i))cnt++;
            match+=cnt;
        }while(cnt);
        return match;
    }
};

void runcase(){
    int n,m,t,k;
    cin >> n >> m >> t >> k;
    vector<int> s(t);
    for(auto &x:s){
        cin >> x;
        x--;
    }
    vector<vector<int>> dist(n,vector<int>(n,INF));
    for(int i=0;i<n;i++){
        dist[i][i]=0;
    }
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        dist[u][v]=dist[v][u]=min(dist[u][v],w);
    }
    for(int x=0;x<n;x++){
        for(int u=0;u<n;u++){
            for(int v=0;v<n;v++){
                dist[u][v]=min(dist[u][v],dist[u][x]+dist[x][v]);
            }
        }
    }
    int l=0,r=INF;
    while(l<r){
        int m=(l+r)/2;
        HopcroftKarp mbm;
        mbm.init(t,n);
        for(int i=0;i<t;i++){
            for(int j=0;j<n;j++){
                if(dist[s[i]][j]<=m){
                    mbm.addEdge(i,j);
                }
            }
        }
        if(mbm.maxMatching()>=k)r=m;
        else l=m+1;
    }
    cout << (l<INF?l:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
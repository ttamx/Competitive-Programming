#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

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
struct Fenwick{
    int n;
    vector<T> t;
    Fenwick(int n=0){init(n);}
    void init(int _n){
        n=_n;
        t.assign(n+1,T{});
    }
    void update(int x,const T &v){
        for(int i=x+1;i<=n;i+=i&-i)t[i]=t[i]+v;
    }
    void update(int l,int r,const T &v){
        update(l,v),update(r+1,-v);
    }
    T query(int x){
        T res{};
        for(int i=x+1;i>0;i-=i&-i)res=res+t[i];
        return res;
    }
    T query(int l,int r){
        return query(r)-query(l-1);
    }
    int find(const T &k){
        int x=0;
        T cur{};
        for(int i=1<<31-__builtin_clz(n);i>0;i>>=1)
            if(x+i<=n&&cur+t[x+i]<k)x+=i,cur=cur+t[x];
        return x;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vi> adj(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    Fenwick<ll> f(n);
    int timer=-1;
    vi tin(n),tout(n),pos(n),siz(n),hv(n,-1);
    function<void(int,int)> tour=[&](int u,int p){
        siz[u]=1;
        tin[u]=++timer;
        pos[timer]=u;
        for(auto v:adj[u])if(v!=p){
            tour(v,u);
            siz[u]+=siz[v];
            if(hv[u]==-1||siz[v]>siz[hv[u]])hv[u]=v;
        }
        tout[u]=timer;
    };
    tour(0,-1);
    vl ans(n),dp(n),dp2(n),dp3(n);
    function<void(int,int,bool)> dfs=[&](int u,int p,bool del){
        for(auto v:adj[u])if(v!=p&&v!=hv[u])dfs(v,u,true);
        if(hv[u]!=-1)dfs(hv[u],u,false);
        f.update(u,1);
        for(auto v:adj[u])if(v!=p&&v!=hv[u]){
            for(int i=tin[v];i<=tout[v];i++)f.update(pos[i],1);
        }
        dp[u]=f.query(u-1);
        if(p!=-1)dp2[u]=f.query(p-1);
        ans[u]=u-dp[u];
        if(del)for(int i=tin[u];i<=tout[u];i++)f.update(pos[i],-1);
    };
    dfs(0,-1,true);
    function<void(int,int)> dfs2=[&](int u,int p){
        for(auto v:adj[u])if(v!=p){
            dfs2(v,u);
            dp3[u]+=dp3[v]+dp[v];
        }
    };
    dfs2(0,-1);
    function<void(int,int,ll)> solve=[&](int u,int p,ll cnt){
        for(auto v:adj[u])if(v!=p){
            solve(v,u,cnt+u-dp2[v]+dp3[u]-dp3[v]-dp[v]);
        }
        ans[u]+=dp[u]+dp3[u]+cnt;
    };
    solve(0,-1,0);
    for(auto x:ans)cout << x << " ";
}
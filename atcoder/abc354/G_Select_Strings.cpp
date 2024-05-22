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

struct RMQ{
    int n,m;
    vector<vi> t;
    RMQ(){}
    RMQ(const vi &a){init(a);}
    void init(const vi &a){
        n=sz(a),m=32-__builtin_clz(n);
        t.assign(m,vi(n));
        t[0]=a;
        for(int i=0;i<m-1;i++)for(int j=0;j+(2<<i)-1<n;j++)
            t[i+1][j]=min(t[i][j],t[i][j+(1<<i)]);
    }
    int query(int l,int r){
        if(r<l)return INF;
        int k=31-__builtin_clz(r-l+1);
        return min(t[k][l],t[k][r-(1<<k)+1]);
    }
};

struct SuffixArray{
    vi sa,lcp,rank;
    SuffixArray(){}
    SuffixArray(const vi &s){init(s);}
    void init(const vi &s){
        int n=sz(s)+1;
        sa=lcp=rank=vi(n);
        iota(1+all(sa),0),sa[0]=n-1;
        sort(1+all(sa),[&](int a,int b){return s[a]<s[b];});
        for(int i=1;i<n;i++){
            int a=sa[i-1],b=sa[i];
            rank[b]=i>1&&s[a]==s[b]?rank[a]:i;
        }
        for(int k=1;k<n;k*=2){
            vi ps(sa),pr(rank),pos(n);
            iota(all(pos),0);
            for(auto i:ps)if((i-=k)>=0)sa[pos[rank[i]]++]=i;
            for(int i=1;i<n;i++){
                int a=sa[i-1],b=sa[i];
                rank[b]=pr[a]==pr[b]&&pr[a+k]==pr[b+k]?rank[a]:i;
            }
        }
        for(int i=0,j,k=0;i<n-1;lcp[rank[i++]]=k)
            for(k&&k--,j=sa[rank[i]-1];j+k<n-1&&s[i+k]==s[j+k];k++);
    }
};

struct Dinic{
    struct Edge{
        int to;
        ll flow,cap;
        Edge(int _to,ll _cap):to(_to),flow(0),cap(_cap){}
        ll getcap(){
            return cap-flow;
        }
    };
    int n;
    ll U;
    vector<Edge> e;
    vector<vi> adj;
    vi ptr,lvl;
    Dinic(){}
    Dinic(int _n){
        init(_n);
    }
    void init(int _n){
        n=_n,U=0;
        e.clear();
        adj.assign(n,{});
    }
    void addEdge(int u,int v,ll cap){
        U=max(U,cap);
        adj[u].emplace_back(sz(e));
        e.emplace_back(v,cap);
        adj[v].emplace_back(sz(e));
        e.emplace_back(u,0); // change 0 to cap for undirected flow
    }
    bool bfs(int s,int t,ll scale){
        lvl.assign(n,0);
        vi q{s};
        lvl[s]=1;
        for(int i=0;i<sz(q);i++){
            int u=q[i];
            for(auto j:adj[u])if(!lvl[e[j].to]&&e[j].getcap()>=scale){
                q.emplace_back(e[j].to);
                lvl[e[j].to]=lvl[u]+1;
            }
        }
        return lvl[t];
    }
    ll dfs(int u,int t,ll f){
        if(u==t||!f)return f;
        for(int &i=ptr[u];i<sz(adj[u]);i++){
            int j=adj[u][i];
            if(lvl[e[j].to]==lvl[u]+1){
                if(ll p=dfs(e[j].to,t,min(f,e[j].getcap()))){
                    e[j].flow+=p;
                    e[j^1].flow-=p;
                    return p;
                }
            }
        }
        return 0;
    }
    ll flow(int s,int t){
        ll flow=0;
        for(ll L=1ll<<(63-__builtin_clzll(U));L>0;L>>=1) // L = 1 may be faster but it's O(V^2 E)
        while(bfs(s,t,L)){
            ptr.assign(n,0);
            while(ll p=dfs(s,t,LINF))flow+=p;
        };
        return flow;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<string> s(n);
    vi a(n);
    for(auto &x:s)cin >> x;
    for(auto &x:a)cin >> x;
    map<string,int> mp;
    for(int i=0;i<n;i++)mp[s[i]]=max(mp[s[i]],a[i]);
    n=sz(mp);
    s.clear();
    a.clear();
    for(auto [x,y]:mp){
        s.emplace_back(x);
        a.emplace_back(y);
    }
    vi v,pos(n),len(n);
    for(int i=0;i<n;i++){
        pos[i]=sz(v);
        len[i]=sz(s[i]);
        for(auto x:s[i])v.emplace_back(x);
        v.emplace_back(-i-1);
    }
    v.pop_back();
    SuffixArray sa(v);
    RMQ rmq(sa.lcp);
    Dinic mf(n*2+2);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(len[i]>=len[j])continue;
            bool ok=false;
            for(int k=0;k<=len[j]-len[i];k++){
                int l=sa.rank[pos[i]],r=sa.rank[pos[j]+k];
                if(l>r)swap(l,r);
                if(rmq.query(l+1,r)>=len[i]){
                    ok=true;
                    break;
                }
            }
            if(!ok)continue;
            mf.addEdge(i*2,j*2+1,1LL*INF*n);
        }
    }
    for(int i=0;i<n;i++){
        mf.addEdge(n*2,i*2,a[i]);
        mf.addEdge(i*2+1,n*2+1,a[i]);
    }
    cout << accumulate(all(a),0LL)-mf.flow(n*2,n*2+1);
}
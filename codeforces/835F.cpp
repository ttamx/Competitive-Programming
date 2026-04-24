#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

#define ALL(a) a.begin(),a.end()
#define RALL(a) a.rbegin(),a.rend()
#define SORT(a) sort(ALL(a))
#define RSORT(a) sort(RALL(a))
#define REV(a) reverse(ALL(a))
#define UNI(a) a.erase(unique(ALL(a)),a.end())
#define SZ(a) (int)(a.size())
#define LB(a,x) (int)(lower_bound(ALL(a),x)-a.begin())
#define UB(a,x) (int)(upper_bound(ALL(a),x)-a.begin())
#define MIN(a) *min_element(ALL(a))
#define MAX(a) *max_element(ALL(a))

using ll = long long;
using db = long double;
using i128 = __int128_t;
using u32 = uint32_t;
using u64 = uint64_t;

const int INF=INT_MAX/2;
const ll LINF=LLONG_MAX/4;
const db DINF=numeric_limits<db>::infinity();
const int MOD=998244353;
const int MOD2=1000000007;
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using PQ = priority_queue<T,vector<T>,greater<T>>;
template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

#define vv(T,a,n,...) vector<vector<T>> a(n,vector<T>(__VA_ARGS__))
#define vvv(T,a,n,m,...) vector<vector<vector<T>>> a(n,vector<vector<T>>(m,vector<T>(__VA_ARGS__)))
#define vvvv(T,a,n,m,k,...) vector<vector<vector<vector<T>>>> a(n,vector<vector<vector<T>>>(m,vector<vector<T>>(k,vector<T>(__VA_ARGS__))))

template<class T,class U>
bool chmin(T &a,U b){return b<a?a=b,1:0;}
template<class T,class U>
bool chmax(T &a,U b){return a<b?a=b,1:0;}
template<class T,class U>
T SUM(const U &a){return accumulate(ALL(a),T{});}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

struct Info{
    ll pre,suf,sum,ans;
    friend Info operator+(Info x,Info y){
        return Info{max(x.pre,y.pre+x.sum),max(y.suf,x.suf+y.sum),x.sum+y.sum,max({x.ans,y.ans,x.suf+y.pre})};
    }
};

struct StackR{
    vector<pair<Info,Info>> dat;
    void push(Info x){
        dat.eb(x,dat.empty()?x:(dat.back().se+x));
    }
};

struct StackL{
    vector<pair<Info,Info>> dat;
    void push(Info x){
        dat.eb(x,dat.empty()?x:(x+dat.back().se));
    }
};

struct Queue{
    StackL l;
    StackR r;
    void push(Info x){
        r.push(x);
    }
    void pop(){
        if(l.dat.empty()){
            REV(r.dat);
            for(auto [x,_]:r.dat)l.push(x);
            r.dat.clear();
        }
        l.dat.pop_back();
    }
    Info get(){
        if(l.dat.empty())return r.dat.back().se;
        if(r.dat.empty())return l.dat.back().se;
        return l.dat.back().se+r.dat.back().se;
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<int> deg(n);
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].eb(v,w);
        adj[v].eb(u,w);
        deg[u]++,deg[v]++;
    }
    bool mark(n);
    queue<int> q;
    for(int i=0;i<n;i++)if(deg[i]==1)q.emplace(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto [v,_]:adj[u])if(deg[v]>1&&--deg[v]==1)q.emplace(v);
    }
    ll base=0;
    function<ll(int,int)> dfs=[&](int u,int p){
        ll mx=0,mx2=0;
        for(auto [v,w]:adj[u])if(v!=p&&deg[v]==1){
            mx2=max(mx2,dfs(v,u)+w);
            if(mx2>mx)swap(mx,mx2);
        }
        base=max(base,mx+mx2);
        return mx;
    };
    ll d=0;
    vector<pair<ll,ll>> a;
    for(int i=0;i<n;i++){
        if(deg[i]==2){
            for(int u=i;;){
                a.eb(d,dfs(u,-1));
                deg[u]=0;
                int x=-1;
                for(auto [v,w]:adj[u]){
                    if(deg[v]==2){
                        x=v;
                        d+=w;
                        break;
                    }
                }
                if(x==-1){
                    for(auto [v,w]:adj[u]){
                        if(v==i){
                            d+=w;
                            break;
                        }
                    }
                    break;
                }
                u=x;
            }
            break;
        }
    }
    int m=SZ(a);
    for(int i=0;i<m;i++)a.eb(a[i].fi+d,a[i].se);
    Queue ds;
    ll ans=LINF;
    ll last=0;
    for(int i=0;i<2*m;i++){
        auto [s,v]=a[i];
        s-=last;
        last+=s;
        ds.push(Info{s+v,v,s,base});
        if(i>=m){
            ds.pop();
            ans=min(ans,ds.get().ans);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
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

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    int cur=0;
    vector<int> sz(n),dep(n),par(n,-1),ans(n),ord;
    pair<int,int> opt(INF,-1);
    function<int(int,int)> dfs=[&](int u,int p){
        sz[u]=1;
        for(auto v:adj[u])if(v!=p)sz[u]+=dfs(v,u);
        return sz[u];
    };
    function<int(int,int)> centroid=[&](int u,int p){
        for(auto v:adj[u])if(v!=p&&sz[v]*2>n)return centroid(v,u);
        return u;
    };
    function<void(int,int)> dfs2=[&](int u,int p){
        ord.emplace_back(u);
        for(auto v:adj[u])if(v!=p){
            par[v]=u;
            dep[v]=dep[u]+1;
            dfs2(v,u);
        }
    };
    dfs(0,-1);
    int c=centroid(0,-1);
    dfs(c,-1);
    dfs2(c,-1);
    for(int i=0;i<n;i++){
        if(i!=c){
            opt=min(opt,mp(sz[i]+dep[i],i));
        }
    }
    auto [u,v]=minmax(opt.second,par[opt.second]);
    ord.erase(find(ALL(ord),v));
    for(int i=0;i<n/2;i++){
        ans[ord[i]]=ans[ord[i+n/2]]=i+1;
    }
    cout << u+1 << " " << v+1 << "\n";
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    int n,k;
    cin >> n >> k;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    vector<pair<int,int>> a;
    for(int i=0;i<k;i++){
        int x;
        cin >> x;
        a.emplace_back(x,i);
    }
    RSORT(a);
    if(n==2){
        auto [f,c]=a[0];
        c++;
        if(f<2){
            cout << -1 << "\n";
        }else{
            cout << c << " " << c << "\n";
        }
        return;
    }
    vector<int> sz(n);
    function<int(int,int)> dfs_sz=[&](int u,int p){
        sz[u]=(SZ(adj[u])==1);
        for(auto v:adj[u])if(v!=p)sz[u]+=dfs_sz(v,u);
        return sz[u];
    };
    int root=-1;
    for(int i=0;i<n;i++){
        if(SZ(adj[i])>1){
            root=i;
            break;
        }
    }
    assert(root!=-1);
    int tot=dfs_sz(root,-1);
    function<int(int,int)> centroid=[&](int u,int p){
        for(auto v:adj[u])if(v!=p&&sz[v]*2>tot)return centroid(v,u);
        return u;
    };
    root=centroid(root,-1);
    vector<int> ord;
    function<void(int,int)> dfs=[&](int u,int p){
        if(SZ(adj[u])==1)ord.eb(u);
        for(auto v:adj[u])if(v!=p)dfs(v,u);
    };
    dfs(root,-1);
    assert(SZ(ord)==tot);
    vector<int> ans(n,-1),good,bad;
    int p=0;
    for(auto [x,c]:a){
        if(x==1){
            bad.eb(c);
            continue;
        }
        if(p<tot/2){
            ans[ord[p]]=ans[ord[p+tot/2]]=c;
            x-=2;
            while(x--&&SZ(good)<n)good.eb(c);
        }else if(tot%2==1&&p==tot/2){
            ans[root]=ans[ord.back()]=c;
            x-=2;
            while(x--&&SZ(good)<n)good.eb(c);
        }else{
            while(x--&&SZ(bad)<n)bad.eb(c);
        }
        p++;
    }
    for(auto x:ord){
        if(ans[x]!=-1)continue;
        if(good.empty()){
            cout << -1 << "\n";
            return;
        }
        ans[x]=good.back();
        good.pop_back();
    }
    bad.insert(bad.end(),ALL(good));
    for(auto &x:ans){
        if(x!=-1)continue;
        assert(!bad.empty());
        x=bad.back();
        bad.pop_back();
    }
    for(auto x:ans){
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
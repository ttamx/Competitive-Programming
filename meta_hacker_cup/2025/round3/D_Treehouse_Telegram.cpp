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

const int N=1e5+5;

int n;
vector<int> adj[N];
int mob[N];
vector<int> divisors[N];
ll cnt[N],dist[N],ans[N];
int sz[N];
bool used[N];

int dfs_sz(int u,int p=0){
    sz[u]=1;
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        sz[u]+=dfs_sz(v,u);
    }
    return sz[u];
}

int centroid(int u,int cnt,int p=0){
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        if(sz[v]*2>cnt)return centroid(v,cnt,u);
    }
    return u;
}

vector<pair<int,ll>> nodes;

void dfs(int u,int p,ll d){
    nodes.emplace_back(u,d);
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        dfs(v,u,d+1);
    }
}

vector<int> to_clear;

inline void insert1(int u,ll d){
    for(auto x:divisors[u]){
        ans[x]+=cnt[x]*d;
        ans[x]+=dist[x];
    }
}

inline void insert2(int u,ll d){
    to_clear.emplace_back(u);
    for(auto x:divisors[u]){
        cnt[x]++;
        dist[x]+=d;
    }
}

void decom(int u){
    u=centroid(u,dfs_sz(u));
    used[u]=true;
    assert(to_clear.empty());
    insert2(u,0);
    for(auto v:adj[u]){
        if(used[v])continue;
        assert(nodes.empty());
        dfs(v,u,1);
        for(auto [x,d]:nodes){
            insert1(x,d);
        }
        for(auto [x,d]:nodes){
            insert2(x,d);
        }
        vector<pair<int,ll>>().swap(nodes);
    }
    for(auto x:to_clear){
        for(auto d:divisors[x]){
            cnt[x]=0;
            dist[x]=0;
        }
    }
    vector<int>().swap(to_clear);
    for(auto v:adj[u]){
        if(used[v])continue;
        decom(v);
    }
}

void runcase(){
    cin >> n;
    cerr << "n = " << n << "\n";
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    decom(1);
    for(int i=1;i<=n;i++){
        ll res=0;
        for(int j=1;i*j<=n;j++){
            res+=mob[j]*ans[i*j];
        }
        cout << res << " \n"[i==n];
    }
    for(int i=1;i<=n;i++){
        vector<int>().swap(adj[i]);
        sz[i]=0;
        used[i]=false;
        cnt[i]=0;
        dist[i]=0;
        ans[i]=0;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    mob[1]=1;
    for(int i=1;i<N;i++){
        for(int j=i*2;j<N;j+=i){
            mob[j]-=mob[i];
        }
        for(int j=i;j<N;j+=i){
            divisors[j].emplace_back(i);
        }
    }
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cerr << "Case #" << i << endl;
        cout << "Case #" << i << ": ";
        runcase();
    }
}
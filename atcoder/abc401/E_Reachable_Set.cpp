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

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n),rev(n);
    vector<int> cnt(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(u<v)swap(u,v);
        adj[u].emplace_back(v);
        rev[v].emplace_back(u);
    }
    vector<int> p(n),sz(n,1);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){return p[u]=u==p[u]?u:fp(p[u]);};
    auto uni=[&](int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return;
        sz[u]+=sz[v];
        p[v]=u;
    };
    int cur=0;
    for(int i=0;i<n;i++){
        if(cnt[i])cur--;
        for(auto j:rev[i]){
            if(cnt[j]==0)cur++;
            cnt[j]++;
        }
        for(auto j:adj[i])uni(i,j);
        cout << (sz[fp(i)]==i+1?cur:-1) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
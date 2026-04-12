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
    int n,q;
    cin >> n >> q;
    vector<int> fa(n),sz(n,1),col(n);
    vector<array<int,2>> dp(n,{1,0});
    iota(fa.begin(),fa.end(),0);
    auto get_root=[&](int u){
        while(u!=fa[u])u=fa[u];
        return u;
    };
    auto get_col=[&](int u){
        int c=0;
        while(u!=fa[u]){
            c^=col[u];
            u=fa[u];
        }
        return c;
    };
    int ans=0;
    bool bad=false;
    auto merge=[&](int u,int v){
        if(ans==-1)return;
        bool f=get_col(u)==get_col(v);
        u=get_root(u),v=get_root(v);
        if(u==v){
            if(f)ans=-1;
            return;
        }
        if(sz[u]<sz[v])swap(u,v);
        ans-=min(dp[v][0],dp[v][1]);
        ans-=min(dp[u][0],dp[u][1]);
        if(f){
            col[v]^=1;
            swap(dp[v][0],dp[v][1]);
        }
        dp[u][0]+=dp[v][0];
        dp[u][1]+=dp[v][1];
        ans+=min(dp[u][0],dp[u][1]);
        fa[v]=u;
        sz[u]+=sz[v];
    };
    while(q--){
        int u,v;
        cin >> u >> v;
        u--,v--;
        merge(u,v);
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
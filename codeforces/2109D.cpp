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
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(k);
    for(auto &x:a)cin >> x;
    ll tot=accumulate(a.begin(),a.end(),0LL);
    ll tot2=-LINF;
    for(auto &x:a){
        if(x&1){
            tot2=max(tot2,tot-x);
        }
    }
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<array<ll,2>> dp(n,{LINF,LINF});
    queue<pair<int,int>> q;
    q.emplace(0,dp[0][0]=0);
    while(!q.empty()){
        auto [u,d]=q.front();
        q.pop();
        int p=d&1^1;
        for(auto v:adj[u]){
            if(dp[v][p]==LINF){
                q.emplace(v,dp[v][p]=d+1);
            }
        }
    }
    int p=tot&1;
    for(int i=0;i<n;i++){
        bool ok=false;
        if(dp[i][p]<=tot)ok=true;
        if(dp[i][p^1]<=tot2)ok=true;
        cout << ok;
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
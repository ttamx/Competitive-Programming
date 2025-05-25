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
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int x;
        cin >> x;
        adj[x-1].emplace_back(i);
    }
    vector<int> sz(n);
    vector<array<int,32>> dp(n),pre(n);
    for(int u=n-1;u>=0;u--){
        sz[u]=1;
        dp[u][a[u]]=1;
        for(auto v:adj[u]){
            sz[u]+=sz[v];
            array<int,32> ndp{};
            for(int i=0;i<32;i++){
                for(int j=0;j<32;j++){
                    ndp[i^j]|=dp[u][i]&dp[v][j];
                }
            }
            pre[v]=dp[u];
            dp[u]=ndp;
        }
        if(sz[u]%2==0){
            dp[u][0]=1;
        }
    }
    if(!dp[0][0]){
        cout << -1 << "\n";
        return;
    }
    vector<int> ans;
    function<void(int,int)> dfs=[&](int u,int val){
        if(val==0&&sz[u]%2==0){
            ans.emplace_back(u);
            return;
        }
        reverse(adj[u].begin(),adj[u].end());
        for(auto v:adj[u]){
            for(int i=0;i<32;i++){
                if(dp[v][i]&pre[v][val^i]){
                    val^=i;
                    dfs(v,i);
                    break;
                }
            }
        }
    };
    dfs(0,0);
    ans.emplace_back(0);
    cout << ans.size() << "\n";
    for(auto x:ans){
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
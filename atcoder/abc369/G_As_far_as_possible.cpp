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

void runcase(){
    int n;
    cin >> n;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vector<ll> a,dp(n);
    function<void(int,int)> dfs=[&](int u,int p){
        ll mx=0;
        int idx=-1;
        for(auto [v,w]:adj[u])if(v!=p){
            dfs(v,u);
            if(idx==-1||dp[v]+w>mx){
                mx=dp[v]+w;
                idx=v;
            }
        }
        dp[u]=mx;
        for(auto [v,w]:adj[u])if(v!=p&&v!=idx){
            a.emplace_back(dp[v]+w);
        }
    };
    dfs(0,-1);
    a.emplace_back(dp[0]);
    sort(a.rbegin(),a.rend());
    while(a.size()<n)a.emplace_back(0);
    for(int i=1;i<n;i++){
        a[i]+=a[i-1];
    }
    for(auto x:a){
        cout << x*2 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
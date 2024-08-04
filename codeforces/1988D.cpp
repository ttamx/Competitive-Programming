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
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<array<pair<ll,ll>,2>> dp(n);
    function<void(int,int)> dfs=[&](int u,int p){
        map<ll,ll> mp;
        ll tot=0;
        for(auto v:adj[u])if(v!=p){
            dfs(v,u);
            tot+=dp[v][0].first;
            mp[dp[v][0].second]+=dp[v][1].first-dp[v][0].first;
        }
        for(int i=1,j=0;j<2;i++)if(!mp.count(i)){
            mp[i]=0;
            j++;
        }
        dp[u][0]=dp[u][1]={LINF,0};
        for(auto &[x,y]:mp){
            y+=tot+1LL*x*a[u];
            dp[u][1]=min(dp[u][1],{y,x});
            if(dp[u][1]<dp[u][0])swap(dp[u][0],dp[u][1]);
        }
    };
    dfs(0,-1);
    cout << dp[0][0].first << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
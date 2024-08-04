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
    vector<vi> adj(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<array<int,2>> dp(n),up(n);
    function<void(int,int)> dfs=[&](int u,int p){
        dp[u]={0,1};
        for(auto v:adj[u])if(v!=p){
            dfs(v,u);
            dp[u][0]+=max(dp[v][0],dp[v][1]);
            dp[u][1]+=dp[v][0];
        }
    };
    function<void(int,int)> dfs2=[&](int u,int p){
        vector<int> ch;
        for(auto v:adj[u])if(v!=p){
            ch.emplace_back(v);
            up[v]={0,1};
        }
        for(int t=0;t<2;t++){
            array<int,2> sum{0,0};
            for(auto v:ch){
                up[v][0]+=sum[0];
                up[v][1]+=sum[1];
                sum[0]+=max(dp[v][0],dp[v][1]);
                sum[1]+=dp[v][0];
            }
            reverse(ch.begin(),ch.end());
        }
        for(auto v:ch){
            if(u){
                up[v][0]+=max(up[u][0],up[u][1]);
                up[v][1]+=up[u][0];
            }
            dfs2(v,u);
        }
    };
    dfs(0,-1);
    dfs2(0,-1);
    for(int i=1;i<n;i++){
        dp[i][0]+=max(up[i][0],up[i][1]);
        dp[i][1]+=up[i][0];
    }
    int ans=0;
    for(int i=0;i<n;i++){
        ans=max(ans,max(dp[i][0]+(adj[i].size()==1),dp[i][1]));
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
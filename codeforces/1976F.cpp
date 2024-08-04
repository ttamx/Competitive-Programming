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
    int n,k;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> dp(n),a;
    function<void(int,int)> dfs=[&](int u,int p){
        int mx=-1;
        for(auto v:adj[u])if(v!=p){
            dfs(v,u);
            if(mx==-1||dp[v]>dp[mx])mx=v;
        }
        if(mx!=-1)dp[u]=dp[mx];
        dp[u]++;
        for(auto v:adj[u])if(v!=p&&v!=mx){
            a.emplace_back(dp[v]);
        }
    };
    dfs(0,-1);
    sort(a.begin(),a.end());
    int ans=n-dp[0];
    for(int i=0;i<n-1;i++){
        cout << ans << " ";
        for(int t=0;t<2;t++){
            if(!a.empty()){
                ans-=a.back();
                a.pop_back();
            }
        }
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
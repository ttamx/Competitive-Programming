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

const int B=8192;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> deg(n);
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        deg[u]++,deg[v]++;
    }
    vector<int> q;
    vector<vector<int>> pre(n);
    for(int i=0;i<n;i++){
        if(deg[i]==a[i]){
            q.emplace_back(i);
        }
    }
    for(int i=0;i<n;i++){
        int u=q[i];
        for(auto v:adj[u]){
            if(deg[v]>a[v]){
                pre[v].emplace_back(u);
                deg[v]--;
                if(deg[v]==a[v]){
                    q.emplace_back(v);
                }
            }
        }
    }
    ll ans=1LL*n*(n+1)/2;
    for(int l=0;l<n;l+=B){
        vector<bitset<B>> dp(n);
        for(int i=l;i<min(l+B,n);i++)dp[i][i-l]=1;
        for(auto u:q){
            for(auto v:pre[u]){
                dp[u]|=dp[v];
            }
            ans-=dp[u].count();
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
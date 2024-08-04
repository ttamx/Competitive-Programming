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
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);z
        adj[v].emplace_back(u,w);
    }
    int b=1<<(k-1);
    vector<vector<ll>> dp(n,vector<ll>(b,LINF));
    for(int i=0;i<n;i++)dp[i][0]=0;
    for(int i=0;i<k-1;i++)dp[i][1<<i]=0;
    for(int i=0;i<b;i++){
        for(int u=0;u<n;u++){
            for(int j=(i-1);j>0;j=(j-1)&i){
                dp[u][i]=min(dp[u][i],dp[u][j]+dp[u][i^j]);
            }
        }
        using P = pair<ll,int>;
        priority_queue<P,vector<P>,greater<P>> pq;
        for(int u=0;u<n;u++)pq.emplace(dp[u][i],u);
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if(d>dp[u][i])continue;
            for(auto [v,w]:adj[u])if(d+w<dp[v][i]){
                dp[v][i]=d+w;
                pq.emplace(d+w,v);
            }
        }
    }
    for(int i=k-1;i<n;i++){
        cout << dp[i][b-1] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
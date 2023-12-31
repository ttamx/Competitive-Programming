#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
    int n,m;
    cin >> n >> m;
    vector<vector<pii>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vl s(n);
    for(auto &x:s)cin >> x;
    using T = tuple<ll,int,int>;
    priority_queue<T,vector<T>,greater<T>> pq;
    vector<vl> dp(n,vl(n,LINF));
    dp[0][0]=0;
    pq.emplace(0,0,0);
    while(!pq.empty()){
        auto [d,i,j]=pq.top();
        pq.pop();
        if(d>dp[i][j])continue;
        for(auto [v,w]:adj[i]){
            ll tmp=d+w*s[j];
            if(tmp<dp[v][v]){
                dp[v][v]=tmp;
                pq.emplace(tmp,v,v);
            }
            if(tmp<dp[v][j]){
                dp[v][j]=tmp;
                pq.emplace(tmp,v,j);
            }
        }
    }
    cout << *min_element(all(dp.back())) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
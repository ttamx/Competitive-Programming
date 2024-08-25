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
    int n,m;
    cin >> n >> m;
    int t0,t1,t2;
    cin >> t0 >> t1 >> t2;
    vector<vector<tuple<int,int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,w1,w2;
        cin >> u >> v >> w1 >> w2;
        u--,v--;
        adj[u].emplace_back(v,w1,w2);
        adj[v].emplace_back(u,w1,w2);
    }
    vector<array<int,3>> dp(n,{-1,-1,-1});
    priority_queue<tuple<int,int,int>> pq;
    dp[n-1][0]=t0;
    pq.emplace(t0,n-1,0);
    while(!pq.empty()){
        auto [d,u,i]=pq.top();
        pq.pop();
        if(d<dp[u][i])continue;
        if(i==0){
            assert(d>=t2);
            if(t2>dp[u][1]){
                dp[u][1]=t2;
                pq.emplace(t2,u,1);
            }
            for(auto [v,w,_]:adj[u]){
                if(d-w>=t2&&d-w>dp[v][i]){
                    dp[v][i]=d-w;
                    pq.emplace(d-w,v,i);
                }
            }
            for(auto [v,_,w]:adj[u]){
                int j=i;
                if(d-w<=t2)j++;
                if(d-w<=t1)j++;
                if(d-w>dp[v][j]){
                    dp[v][j]=d-w;
                    pq.emplace(d-w,v,j);
                }
            }
        }else if(i==1){
            assert(d<=t2&&d>=t1);
            if(t1>dp[u][2]){
                dp[u][2]=t1;
                pq.emplace(t1,u,2);
            }
            for(auto [v,_,w]:adj[u]){
                int j=i;
                if(d-w<=t1)j++;
                if(d-w>dp[v][j]){
                    dp[v][j]=d-w;
                    pq.emplace(d-w,v,j);
                }
            }
        }else{
            assert(d<=t1);
            for(auto [v,w,_]:adj[u]){
                if(d-w>dp[v][i]){
                    dp[v][i]=d-w;
                    pq.emplace(d-w,v,i);
                }
            }
        }
    }
    cout << *max_element(dp[0].begin(),dp[0].end()) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
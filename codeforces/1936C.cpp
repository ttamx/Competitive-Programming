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
    vector<int> c(n);
    vector<vector<int>> a(n,vector<int>(m));
    vector<vector<int>> vals(m);
    for(auto &x:c)cin >> x;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> a[i][j];
            vals[j].emplace_back(a[i][j]);
        }
    }
    int cur_node=n;
    vector<vector<int>> ids(m);
    vector<tuple<int,int,int>> edges;
    for(int i=0;i<m;i++){
        sort(vals[i].begin(),vals[i].end());
        vals[i].erase(unique(vals[i].begin(),vals[i].end()),vals[i].end());
        int s=vals[i].size();
        for(int j=0;j<s;j++){
            ids[i].emplace_back(cur_node++);
        }
        for(int j=1;j<s;j++){
            edges.emplace_back(ids[i][j],ids[i][j-1],vals[i][j]-vals[i][j-1]);
            edges.emplace_back(ids[i][j-1],ids[i][j],0);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int x=lower_bound(vals[j].begin(),vals[j].end(),a[i][j])-vals[j].begin();
            edges.emplace_back(ids[j][x],i,c[i]);
            edges.emplace_back(i,ids[j][x],0);
        }
    }
    vector<vector<pair<int,int>>> adj(cur_node);
    for(auto [u,v,w]:edges){
        adj[u].emplace_back(v,w);
    }
    priority_queue<pll,vector<pll>,greater<pll>> pq;
    vector<ll> dp(cur_node,LINF);
    dp[0]=0;
    pq.emplace(0,0);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        for(auto [v,w]:adj[u]){
            if(d+w<dp[v]){
                dp[v]=d+w;
                pq.emplace(d+w,v);
            }
        }
    }
    cout << dp[n-1] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    vi dp(n),pa(n);
    function<void(int,int)> dfs=[&](int u,int p){
        dp[u]=p!=-1?dp[p]+1:0;
        pa[u]=p;
        for(auto v:adj[u])if(v!=p)dfs(v,u);
    };
    dfs(0,-1);
    int rt=max_element(all(dp))-dp.begin();
    dfs(rt,-1);
    deque<int> dq;
    int col=0;
    vi ans(n,-1);
    int c=0;
    for(int u=max_element(all(dp))-dp.begin();u!=-1;u=pa[u])dq.emplace_back(u);
    while(!dq.empty()){
        ans[dq.front()]=c;
        c^=1;
        dq.pop_front();
        if(!dq.empty()){
            ans[dq.back()]=c;
            c^=1;
            dq.pop_back();
        }
    }
    for(auto &x:ans)if(x==-1)x=c,c^=1;
    for(auto x:ans)cout << "RB"[x];
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
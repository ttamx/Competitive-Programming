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
    vector<vector<int>> adj(n);
    vector<int> deg(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        deg[u]++,deg[v]++;
    }
    vector<int> col(n);
    function<void(int,int)> dfs=[&](int u,int p){
        for(auto v:adj[u])if(v!=p){
            col[v]=col[u]^1;
            dfs(v,u);
        }
    };
    dfs(0,-1);
    vector<queue<int>> q(2);
    for(int i=0;i<n;i++){
        if(deg[i]==1){
            q[col[i]].emplace(i);
        }
    }
    for(int i=0;i<n/2;i++){
        assert(!q[0].empty()&&!q[1].empty());
        for(auto &qq:q){
            int u=qq.front();
            qq.pop();
            cout << u+1 << " ";
            for(auto v:adj[u]){
                deg[v]--;
                if(deg[v]==1){
                    q[col[v]].emplace(v);
                }
            }
        }
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
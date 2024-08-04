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
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> a(n),val(n);
    for(auto &x:a)cin >> x;
    queue<int> q;
    for(int i=0;i<n;i++){
        if(val[i]==a[i]){
            q.emplace(i);
        }
    }
    vector<int> ans;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(val[u]!=a[u])continue;
        ans.emplace_back(u);
        val[u]++;
        for(auto v:adj[u]){
            val[v]++;
            if(val[v]==a[v]){
                q.emplace(v);
            }
        }
    }
    cout << ans.size() << "\n";
    for(auto x:ans)cout << x+1 << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
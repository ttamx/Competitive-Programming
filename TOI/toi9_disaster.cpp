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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<pii>> adj(26);
    int m=0;
    for(int i=0;i<n;i++){
        char u,v;
        cin >> u >> v;
        u-='A',v-='A';
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
        m=max({m,int(u),int(v)});
    }
    m++;
    int st=0;
    for(int i=0;i<m;i++)if(sz(adj[i])%2)st=i;
    vi ptr(m),used(n),ans;
    function<void(int)> dfs=[&](int u){
        for(int &p=ptr[u];p<sz(adj[u]);p++){
            auto [v,i]=adj[u][p];
            if(used[i])continue;
            used[i]=true;
            dfs(v);
        }
        ans.emplace_back(u);
    };
    dfs(st);
    for(auto x:ans)cout << char('A'+x) << " ";
}
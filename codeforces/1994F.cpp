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
    vector<tuple<int,int,int>> edge(m);
    vector<vector<pair<int,int>>> adj(n),adj2(n);
    vector<int> deg(n);
    for(int i=0;i<m;i++){
        auto &[u,v,c]=edge[i];
        cin >> u >> v >> c;
        u--,v--;
        if(c){
            deg[u]++,deg[v]++;
            adj2[u].emplace_back(v,i);
            adj2[v].emplace_back(u,i);
        }else{
            adj[u].emplace_back(v,i);
            adj[v].emplace_back(u,i);
        }
    }
    vector<bool> vis(n);
    function<void(int)> dfs=[&](int u){
        vis[u]=true;
        for(auto [v,i]:adj[u])if(!vis[v]){
            dfs(v);
            if(deg[v]&1){
                adj2[u].emplace_back(v,i);
                adj2[v].emplace_back(u,i);
                deg[u]++,deg[v]++;
            }
        }
    };
    for(int i=0;i<n;i++)if(!vis[i])dfs(i);
    for(int i=0;i<n;i++)if(deg[i]&1)return void(cout << "NO\n");
    vector<bool> used(m);
    vector<int> id(n);
    vector<int> ans;
    function<void(int)> dfs2=[&](int u){
        for(int &i=id[u];i<adj2[u].size();i++){
            auto [v,j]=adj2[u][i];
            if(!used[j]){
                used[j]=true;
                dfs2(v);
            }
        }
        ans.emplace_back(u);
    };
    dfs2(0);
    reverse(ans.begin(),ans.end());
    cout << "YES\n";
    cout << ans.size()-1 << "\n";
    for(auto x:ans)cout << x+1 << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
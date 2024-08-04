#include<bits/stdc++.h>

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
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> a(n);
    for(auto &x:a)cin >> x,x--;
    vector<int> sz(n);
    vector<bool> used(n);
    function<int(int,int)> dfs_sz=[&](int u,int p){
        sz[u]=1;
        for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfs_sz(v,u);
        return sz[u];
    };
    function<int(int,int,int)> centroid=[&](int u,int p,int s){
        for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>s)return centroid(v,u,s);
        return u;
    };
    vector<pair<int,int>> path;
    function<void(int,int,int)> dfs=[&](int u,int p,int d){
        path.emplace_back(u,d);
        for(auto v:adj[u])if(v!=p&&!used[v])dfs(v,u,d+1);
    };
    ll ans=0;
    vector<ll> cnt(n),sum(n);
    function<void(int)> decom=[&](int u){
        u=centroid(u,-1,dfs_sz(u,-1));
        used[u]=true;
        vector<int> res{a[u]};
        cnt[a[u]]++;
        ll p=ans;
        for(auto v:adj[u])if(!used[v]){
            dfs(v,u,1);
            for(auto [x,d]:path){
                res.emplace_back(a[x]);
                ans+=cnt[a[x]]*d;
                ans+=sum[a[x]];
            }
            for(auto [x,d]:path){
                cnt[a[x]]++;
                sum[a[x]]+=d;
            }
            path.clear();
        }
        for(auto x:res)cnt[x]=sum[x]=0;
        for(auto v:adj[u])if(!used[v])decom(v);
    };
    decom(0);
    cout << ans << "\n";
}
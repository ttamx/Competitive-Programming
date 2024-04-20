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
    vi a(n);
    for(auto &x:a)cin >> x,x--;
    vector<vi> adj(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vi siz(n),used(n);
    function<int(int,int)> get_sz=[&](int u,int p){
        siz[u]=1;
        for(auto v:adj[u])if(v!=p&&!used[v])siz[u]+=get_sz(v,u);
        return siz[u];
    };
    function<int(int,int,int)> centroid=[&](int u,int p,int cnt){
        for(auto v:adj[u])if(v!=p&&!used[v]&&siz[v]>cnt/2)return centroid(v,u,cnt);
        return u;
    };
    ll ans=0;
    vi cnt(n),cnt2(n);
    function<void(int,int)> dfs1=[&](int u,int p){
        if(++cnt2[a[u]]==1)ans+=cnt[a[u]];
        for(auto v:adj[u])if(v!=p&&!used[v])dfs1(v,u);
        --cnt2[a[u]];
    };
    function<void(int,int)> dfs2=[&](int u,int p){
        if(++cnt2[a[u]]==1)cnt[a[u]]++;
        for(auto v:adj[u])if(v!=p&&!used[v])dfs2(v,u);
        --cnt2[a[u]];
    };
    function<void(int,int)> dfs3=[&](int u,int p){
        if(++cnt2[a[u]]==1)cnt[a[u]]--;
        for(auto v:adj[u])if(v!=p&&!used[v])dfs3(v,u);
        --cnt2[a[u]];
    };
    function<void(int)> decom=[&](int u){
        u=centroid(u,-1,get_sz(u,-1));
        used[u]=1;
        cnt[a[u]]++;
        for(auto v:adj[u])if(!used[v]){
            dfs1(v,u);
            cnt2[a[u]]++;
            dfs2(v,u);
            cnt2[a[u]]--;
        }
        cnt[a[u]]--;
        cnt2[a[u]]++;
        for(auto v:adj[u])if(!used[v])dfs3(v,u);
        cnt2[a[u]]--;
        for(auto v:adj[u])if(!used[v])decom(v);
    };
    decom(0);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
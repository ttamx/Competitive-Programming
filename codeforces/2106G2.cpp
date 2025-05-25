#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    auto ask=[&](vector<int> a){
        cout << "? 1 " << a.size();
        for(auto x:a)cout << " " << x+1;
        cout << endl;
        int res;
        cin >> res;
        return res;
    };
    vector<int> memo;
    auto toggle=[&](int x){
        memo.emplace_back(x);
        cout << "? 2 " << x+1 << endl;
    };
    vector<int> base(n);
    for(int i=0;i<n;i++)base[i]=ask({i});
    auto ask2=[&](vector<int> a){
        int res=0;
        for(auto x:a)res+=base[x];
        return res;
    }; 
    vector<int> sz(n);
    vector<bool> used(n);
    function<int(int,int)> dfs=[&](int u,int p)->int {
        sz[u]=1;
        for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfs(v,u);
        return sz[u];
    };
    function<int(int,int,int)> centroid=[&](int u,int p,int cnt)->int {
        for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>cnt)return centroid(v,u,cnt);
        return u;
    };
    vector<int> cur;
    function<void(int,int)> dfs2=[&](int u,int p)->void {
        cur.emplace_back(u);
        for(auto v:adj[u])if(v!=p&&!used[v])dfs2(v,u);
    };
    int root=-1;
    function<void(int)> decom=[&](int u){
        u=centroid(u,-1,dfs(u,-1));
        used[u]=true;
        vector<int> a;
        for(auto v:adj[u])if(!used[v])a.emplace_back(v);
        if(a.empty()){
            root=u;
            return;
        }
        int l=0,r=a.size();
        toggle(u);
        while(l<r){
            int m=(l+r)/2;
            for(int i=l;i<=m;i++)dfs2(a[i],-1);
            int d=abs(ask(cur)-ask2(cur));
            if(d<2*cur.size())r=m;
            else l=m+1;
            cur.clear();
        }
        if(l==a.size()){
            root=u;
            return;
        }
        decom(a[l]);
    };
    decom(0);
    assert(root!=-1);
    auto ans=base;
    function<void(int,int)> dfs3=[&](int u,int p)->void {
        for(auto v:adj[u])if(v!=p){
            dfs3(v,u);
            ans[v]-=ans[u];
        }
    };
    dfs3(root,-1);
    for(auto x:memo)ans[x]*=-1;
    cout << "!";
    for(auto x:ans)cout << " " << x;
    cout << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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

const int B=30;

struct Gauss{
    array<int,B> basis;
    Gauss():basis{}{}
    void insert(int x){
        for(int i=B-1;i>=0;i--)if(x>>i&1){
            if(!basis[i]){
                basis[i]=x;
                return;
            }
            x^=basis[i];
        }
    }
    int min(int x){
        for(int i=B-1;i>=0;i--)if(x>>i&1){
            x^=basis[i];
        }
        return x;
    }
};

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    Gauss g;
    vector<int> a(n);
    vector<bool> vis(n);
    function<void(int)> dfs=[&](int u){
        vis[u]=true;
        for(auto [v,w]:adj[u]){
            if(!vis[v]){
                a[v]=a[u]^w;
                dfs(v);
            }else g.insert(a[u]^a[v]^w);
        }
    };
    dfs(0);
    ll ans=0;
    vector<int> cnt(31*n);
    vector<array<int,2>> ch(31*n);
    int buf=1;
    auto insert=[&](int x){
        int u=1;
        cnt[u]++;
        for(int i=B-1;i>=0;i--){
            int c=x>>i&1;
            if(!ch[u][c])ch[u][c]=++buf;
            u=ch[u][c];
            cnt[u]++;
        }
    };
    auto query=[&](int x){
        int u=1;
        for(int i=B-1;i>=0;i--){
            int c=x>>i&1;
            if(k>>i&1){
                ans+=cnt[ch[u][c]];
                c^=1;
            }
            u=ch[u][c];
        }
        ans+=cnt[u];
    };
    for(auto x:a){
        x=g.min(x);
        query(x);
        insert(x);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
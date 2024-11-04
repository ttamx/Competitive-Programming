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
    int n,root;
    cin >> n >> root;
    root--;
    vector<int> a(n);
    ll sum=0;
    for(auto &x:a){
        cin >> x;
        sum+=x;
    }
    if(sum==0){
        cout << 0 << "\n";
        return;
    }
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    ll ans=LINF;
    for(int c=0;c<n;c++){
        function<ll(int,int,ll)> dfs=[&](int u,int p,ll val){
            ll res=a[u];
            for(auto v:adj[u]){
                if(v==p)continue;
                res+=dfs(v,u,val);
            }
            res-=val;
            if(u<=c)res--;
            if(res<0){
                res=res&1;
            }
            return res;
        };
        for(int d=0;d<2;d++){
            if((n*d+c+1)%2!=sum%2)continue;
            ll l=0,r=1e9;
            while(l<r){
                ll m=(l+r)/2;
                ll val=m*2+d;
                if(dfs(root,-1,m*2+d)<=1)r=m;
                else l=m+1;
            }
            ans=min(ans,(l*2+d)*n+c+1);
        }
    }
    cout << (ans<LINF?ans:-1LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
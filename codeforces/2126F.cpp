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
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<tuple<int,int,int>> edges(n-1);
    vector<vector<pair<int,int>>> adj(n);
    ll base=0;
    for(int i=0;i<n-1;i++){
        auto &[u,v,c]=edges[i];
        cin >> u >> v >> c;
        u--,v--;
        adj[u].emplace_back(v,c);
        adj[v].emplace_back(u,c);
        base+=c;
    }
    vector<bool> isbig(n);
    vector<int> big;
    for(int i=0;i<n;i++){
        if(1LL*adj[i].size()*adj[i].size()>=n){
            isbig[i]=true;
            big.emplace_back(i);
        }
    }
    ll cur=0;
    for(auto [u,v,c]:edges){
        if(!isbig[u]&&!isbig[v]&&a[u]==a[v]){
            cur+=c;
        }
    }
    auto aa=a;
    vector<pair<int,int>> qr(q);
    vector<ll> ans;
    for(auto &[u,x]:qr){
        cin >> u >> x;
        u--,x--;
        if(!isbig[u]){
            for(auto [v,c]:adj[u]){
                if(!isbig[v]){
                    if(a[v]==a[u]){
                        cur-=c;
                    }
                    if(a[v]==x){
                        cur+=c;
                    }
                }
            }
        }
        a[u]=x;
        ans.emplace_back((base-cur)*2);
    }
    for(auto u:big){
        a=aa;
        vector<int> cost(n);
        vector<ll> b(n);
        for(auto [v,c]:adj[u]){
            cost[v]=(!isbig[v]?2*c:c);
            b[a[v]]+=cost[v];
        }
        for(int i=0;i<q;i++){
            auto [v,x]=qr[i];
            b[a[v]]-=cost[v];
            b[a[v]=x]+=cost[v];
            ans[i]-=b[a[u]];
        }
    }
    for(auto x:ans){
        assert(x%2==0);
        cout << x/2 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    int n,m;
    cin >> n >> m;
    set<pair<int,int>> used;
    vector<set<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace(v);
        adj[v].emplace(u);
        used.emplace(minmax(u,v));
    }
    set<int> s;
    vector<int> cnt(n);
    vector<int> cur;
    vector<bool> vis(n);
    for(int i=0;i<n;i++){
        s.emplace(i);
    }
    auto upd=[&](int u){
        s.erase(u);
        for(auto v:adj[u]){
            cnt[v]++;
        }
        cur.emplace_back(u);
        vis[u]=true;
    };
    upd(0);
    vector<pair<int,int>> ans;
    while(true){
        vector<int> to_upd;
        for(auto x:s){
            if(cnt[x]<cur.size()){
                to_upd.emplace_back(x);
                bool ok=false;
                for(auto u:cur){
                    if(!adj[x].count(u)){
                        ans.emplace_back(u,x);
                        ok=true;
                        break;
                    }
                }
                assert(ok);
            }
        }
        if(to_upd.empty()){
            break;
        }
        for(auto x:to_upd){
            upd(x);
        }
    }
    if(cur.size()<n){
        cout << -1 << "\n";
        return;
    }
    for(auto [u,v]:ans){
        used.emplace(minmax(u,v));
    }
    for(int u=0;u<n;u++){
        if(ans.size()==m)break;
        for(int v=u+1;v<n;v++){
            if(ans.size()==m)break;
            if(!used.count(make_pair(u,v))){
                ans.emplace_back(u,v);
            }
        }
    }
    if(ans.size()<m){
        cout << -1 << "\n";
        return;
    }
    for(auto [u,v]:ans){
        cout << u+1 << " " << v+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
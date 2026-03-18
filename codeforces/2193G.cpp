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
    vector<vector<int>> adj(n+1);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    auto ask=[&](int u,int v){
        cout << "? " << u << " " << v << endl;
        int res;
        cin >> res;
        return res;
    };
    auto answer=[&](int x){
        cout << "! " << x << endl;
    };
    vector<pair<int,int>> a;
    function<int(int,int)> dfs=[&](int u,int p){
        int c=u;
        for(auto v:adj[u])if(v!=p){
            int x=dfs(v,u);
            if(x){
                if(c){
                    a.emplace_back(x,c);
                    c=0;
                }else{
                    c=x;
                }
            }
        }
        return c;
    };
    int x=dfs(1,0);
    for(auto [u,v]:a){
        if(ask(u,v)){
            if(ask(u,u)){
                answer(u);
            }else{
                answer(v);
            }
            return;
        }
    }
    answer(x);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
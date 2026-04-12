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
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<bool> c(n);
    int st;
    for(int i=0;i<m;i++){
        cin >> st;
        st--;
        c[st]=true;
    }
    int base=0;
    pair<int,int> ans(0,-st);
    function<pair<int,int>(int,int)> dfs=[&](int u,int p){
        pair<int,int> mx(0,-u),mx2(0,-u);
        for(auto v:adj[u])if(v!=p){
            auto t=dfs(v,u);
            if(c[v]){
                t.first++;
                c[u]=true;
                base+=2;
                mx2=max(mx2,t);
                if(mx2>mx)swap(mx,mx2);
            }
        }
        if(c[u])ans=max(ans,{mx.first+mx2.first,max(mx.second,mx2.second)});
        return mx;
    };
    dfs(st,-1);
    cout << 1-ans.second << "\n";
    cout << base-ans.first << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
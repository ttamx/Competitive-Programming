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
    vector<int> col(n),dep(n);
    function<void(int,int,int)> dfs=[&](int u,int p,int d){
        for(auto v:adj[u]){
            if(v==p)continue;
            col[v]=col[u]^1;
            dep[v]=dep[u]+1;
            dfs(v,u,d+1);
        }
    };
    dfs(n-1,-1,0);
    int mx=*max_element(dep.begin(),dep.end());
    vector<vector<vector<int>>> a(mx+1,vector<vector<int>>(2));
    for(int i=0;i<n;i++){
        a[dep[i]][col[i]].emplace_back(i);
    }
    int cur=col[0]^1;
    vector<pair<int,int>> ans;
    for(int i=mx;i>0;i--){
        for(int j=0;j<a[i][cur].size();j++){
            if(j>0){
                ans.emplace_back(1,0);
                ans.emplace_back(1,0);
            }
            ans.emplace_back(2,a[i][cur][j]);
        }
        ans.emplace_back(1,0);
        cur^=1;
        for(int j=0;j<a[i][cur].size();j++){
            if(j>0){
                ans.emplace_back(1,0);
                ans.emplace_back(1,0);
            }
            ans.emplace_back(2,a[i][cur][j]);
        }
    }
    cout << ans.size() << "\n";
    for(auto [x,y]:ans){
        if(x==1){
            cout << x << "\n";
        }else{
            cout << x << " " << y+1 << "\n";
        }
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
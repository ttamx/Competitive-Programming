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
    bool ok=true;
    vector<vector<pair<int,int>>> ch(n);
    vector<int> dep(n);
    function<void(int,int)> dfs=[&](int u,int p){
        for(auto v:adj[u]){
            if(v!=p){
                dep[v]=dep[u]+1;
                dfs(v,u);
            }
        }
    };
    dep[0]=0;
    dfs(0,-1);
    int rt=max_element(dep.begin(),dep.end())-dep.begin();
    function<int(int,int)> dfs1=[&](int u,int p){
        int mx=0;
        for(auto v:adj[u]){
            if(v!=p){
                int d=dfs1(v,u);
                ch[u].emplace_back(d,v);
                mx=max(mx,d);
            }
        }
        sort(ch[u].rbegin(),ch[u].rend());
        if(ch[u].size()>=2&&ch[u][1].first>1){
            ok=false;
        }
        return mx+1;
    };
    dfs1(rt,-1);
    if(!ok){
        cout << "No\n";
        return;
    }
    vector<int> ans;
    function<void(int,int)> dfs2=[&](int u,int c){
        if(c==0){
            ans.emplace_back(u);
            for(auto [d,v]:ch[u]){
                dfs2(v,1);
            }
        }else{
            reverse(ch[u].begin(),ch[u].end());
            for(auto [d,v]:ch[u]){
                dfs2(v,0);
            }
            ans.emplace_back(u);
        }
    };
    dfs2(rt,0);
    cout << "Yes\n";
    for(auto x:ans){
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
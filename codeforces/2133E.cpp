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
    vector<int> deg(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        deg[u]++,deg[v]++;
    }
    vector<bool> del(n);
    vector<pair<int,int>> ans;
    function<int(int,int)> dfs=[&](int u,int p){
        int ch=0;
        for(auto v:adj[u]){
            if(v==p)continue;
            ch+=dfs(v,u);
        }
        if(ch>=3){
            del[u]=true;
            ans.emplace_back(2,u);
            ans.emplace_back(1,u);
            for(auto v:adj[u]){
                deg[v]--;
            }
            return 0;
        }else if(ch==2){
            return 3;
        }
        return 1;
    };
    dfs(0,-1);
    function<void(int)> dfs2=[&](int u){
        ans.emplace_back(1,u);
        del[u]=true;
        int cnt=0;
        for(auto v:adj[u]){
            if(del[v])continue;
            assert(++cnt<2);
            dfs2(v);
        }
    };
    for(int i=0;i<n;i++){
        if(!del[i]&&deg[i]<2){
            dfs2(i);
        }
    }
    for(int i=0;i<n;i++){
        assert(del[i]);
    }
    cout << ans.size() << "\n";
    for(auto [t,u]:ans){
        cout << t << " " << u+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    map<int,vector<pair<int,int>>> adj;
    map<int,int> deg;
    for(int i=0;i<n;i++){
        int u,v;
        cin >> u >> v;
        v=~v;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
        deg[u]++,deg[v]++;
    }
    int st=deg.begin()->first;
    int cnt=0;
    for(auto [u,d]:deg){
        if(d&1){
            cnt++;
            st=u;
        }
    }
    if(cnt>2){
        cout << "NO\n";
        return;
    }
    vector<bool> used(n);
    map<int,int> ptr;
    vector<int> ord;
    function<void(int)> dfs=[&](int u){
        auto &cur=adj[u];
        for(int &i=ptr[u];i<cur.size();i++){
            auto [v,j]=cur[i];
            if(used[j])continue;
            used[j]=true;
            dfs(v);
            ord.emplace_back(j);
        }
    };
    dfs(st);
    if(ord.size()!=n){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for(auto x:ord){
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
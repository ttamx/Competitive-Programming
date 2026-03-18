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
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x,x--;
    for(auto &x:b)cin >> x,x--;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<n;i++){
        adj[a[i]].emplace_back(b[i],i);
        adj[b[i]].emplace_back(a[i],~i);
    }
    for(int i=0;i<n;i++){
        if(adj[i].size()%2!=0){
            cout << -1 << "\n";
            return;
        }
    }
    vector<int> ans;
    vector<bool> mark(n);
    function<void(int)> dfs=[&](int u){
        while(!adj[u].empty()){
            auto [v,i]=adj[u].back();
            adj[u].pop_back();
            int j=i<0?~i:i;
            if(mark[j])continue;
            mark[j]=true;
            if(i>=0)ans.emplace_back(i);
            dfs(v);
        }
    };
    for(int i=0;i<n;i++)dfs(i);
    cout << ans.size() << "\n";
    for(auto x:ans)cout << x+1 << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
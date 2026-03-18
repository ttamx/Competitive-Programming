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
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    bool ok=true;
    vector<int> ans;
    function<int(int,int)> dfs=[&](int u,int p){
        vector<int> ch;
        for(auto [v,i]:adj[u]){
            if(v==p)continue;
            int c=dfs(v,u);
            if(c>0)ch.emplace_back(c);
            else ans.emplace_back(i);
        }
        if(ch.empty())return 1;
        if(ch.size()==1)return (ch[0]+1)%3;
        if(ch.size()>2){
            ok=false;
            return 0;
        }
        int c=ch[0]+ch[1]+1;
        if(c>3){
            ok=false;
            return 0;
        }
        return 0;
    };
    if(dfs(0,-1)||!ok){
        cout << -1 << "\n";
    }else{
        cout << ans.size() << "\n";
        for(auto x:ans)cout << x+1 << " ";
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    string a,b;
    cin >> a >> b;
    int m;
    cin >> m;
    vector<int> id(n,-1);
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(u==v)id[u]=i;
        else adj[u].emplace_back(v,i);
    }
    vector<int> ans;
    queue<int> q;
    for(int i=0;i<n;i++){
        if(a[i]=='1'){
            q.emplace(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto [v,i]:adj[u]){
            if(a[v]=='0'){
                a[v]^=1;
                q.emplace(v);
                ans.emplace_back(i);
            }
        }
    }
    vector<int> ord;
    vector<bool> vis(n);
    for(int i=0;i<n;i++){
        if(a[i]=='0'&&b[i]=='1'){
            cout << -1 << "\n";
            return;
        }
        if(a[i]=='1'&&(b[i]=='1'||id[i]!=-1)){
            ord.emplace_back(i);
            vis[i]=true;
        }
    }
    vector<int> par(n,-1);
    for(int i=0;i<ord.size();i++){
        int u=ord[i];
        for(auto [v,j]:adj[u]){
            if(!vis[v]){
                vis[v]=true;
                par[v]=u;
                ord.emplace_back(v);
            }
        }
    }
    reverse(ord.begin(),ord.end());
    for(auto u:ord){
        assert(a[u]=='1');
        for(auto [v,i]:adj[u]){
            if(par[v]==u&&a[v]!=b[v]){
                a[v]^=1;
                ans.emplace_back(i);
            }
        }
    }
    for(int i=0;i<n;i++){
        if(a[i]!=b[i]){
            if(a[i]=='0'||id[i]==-1){
                cout << -1 << "\n";
                return;
            }
            ans.emplace_back(id[i]);
        }
    }
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
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
    int m;
    cin >> m;
    vector<vector<int>> a(m);
    vector<int> vals;
    for(auto &x:a){
        int s;
        cin >> s;
        x.resize(s);
        for(auto &y:x){
            cin >> y;
            vals.emplace_back(y);
        }
    }
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    int n=vals.size();
    vector<vector<pair<int,int>>> adj(n+m);
    int idx=0;
    vector<int> pos;
    for(int i=0;i<m;i++){
        for(int j=0;j<a[i].size();j++){
            a[i][j]=lower_bound(vals.begin(),vals.end(),a[i][j])-vals.begin();
            adj[i].emplace_back(a[i][j]+m,idx);
            adj[a[i][j]+m].emplace_back(i,idx);
            pos.emplace_back(j);
            idx++;
        }
    }
    for(int i=0;i<n+m;i++){
        if(adj[i].size()%2!=0){
            cout << "NO\n";
            return;
        }
    }
    vector<bool> vis(idx),vis2(n+m);
    vector<int> id(n+m);
    vector<string> ans(m);
    for(int i=0;i<m;i++){
        ans[i]=string((int)a[i].size(),'L');
    }
    function<void(int)> dfs=[&](int u){
        vis2[u]=true;
        for(int &i=id[u];i<adj[u].size();i++){
            auto [v,j]=adj[u][i];
            if(!vis[j]){
                vis[j]=true;
                if(u<m){
                    ans[u][pos[j]]='R';
                }
                dfs(v);
            }
        }
    };
    for(int i=0;i<m;i++){
        if(!vis2[i]){
            dfs(i);
        }
    }
    cout << "YES\n";
    for(auto x:ans){
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
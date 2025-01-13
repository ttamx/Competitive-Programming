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
    vector<tuple<int,int,int>> edges(m);
    vector<int> vals{0};
    for(auto &[u,v,w]:edges){
        cin >> u >> v >> w;
        u--,v--;
        vals.emplace_back(w);
    }
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    auto check=[&](int mid){
        vector<vector<int>> adj(n),rev(n);
        for(auto [u,v,w]:edges){
            adj[u].emplace_back(v);
            rev[v].emplace_back(u);
            if(w<=vals[mid]){
                adj[v].emplace_back(u);
                rev[u].emplace_back(v);
            }
        }
        vector<bool> vis(n);
        vector<int> st;
        auto dfs=[&](auto &&self,int u){
            if(vis[u])return;
            vis[u]=true;
            for(auto v:adj[u]){
                self(self,v);
            }
            st.emplace_back(u);
        };
        for(int i=0;i<n;i++){
            dfs(dfs,i);
        }
        vis.assign(n,false);
        int scc_id=0;
        vector<int> scc(n);
        auto dfs2=[&](auto &&self,int u){
            if(vis[u])return;
            vis[u]=true;
            scc[u]=scc_id;
            for(auto v:rev[u]){
                self(self,v);
            }
        };
        reverse(st.begin(),st.end());
        for(auto u:st){
            if(!vis[u]){
                dfs2(dfs2,u);
                scc_id++;
            }
        }
        vector<int> deg(scc_id);
        for(int u=0;u<n;u++){
            for(auto v:adj[u]){
                if(scc[u]!=scc[v]){
                    deg[scc[v]]++;
                }
            }
        }
        return count(deg.begin(),deg.end(),0)==1;
    };
    check(0);
    int l=0,r=vals.size();
    while(l<r){
        int m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    cout << (l<vals.size()?vals[l]:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
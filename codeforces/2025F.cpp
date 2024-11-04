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
    vector<vector<tuple<int,int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v,i,0);
        adj[v].emplace_back(u,i,1);
    }
    vector<bool> vis(n);
    vector<int> ans(m,-1),ans2(m,-1);
    function<void(int,int,int)> dfs=[&](int u,int p,int pi){
        vis[u]=true;
        vector<pair<int,int>> ch;
        for(auto [v,i,c]:adj[u]){
            if(i==p)continue;
            if(!vis[v]){
                dfs(v,i,c^1);
            }
            if(ans[i]==-1){
                ch.emplace_back(i,c);
            }
        }
        while(ch.size()>1){
            auto [x,xi]=ch.back();
            ch.pop_back();
            auto [y,yi]=ch.back();
            ch.pop_back();
            ans[x]=xi;
            ans[y]=yi;
            ans2[x]=x<y;
            ans2[y]=y<x;
        }
        if(!ch.empty()){
            auto [x,xi]=ch[0];
            if(p!=-1){
                ans[x]=xi;
                ans[p]=pi;
                ans2[x]=x<p;
                ans2[p]=p<x;
            }else{
                ans[x]=xi;
                ans2[x]=1;
            }
        }
    };
    for(int i=0;i<n;i++){
        if(!vis[i]){
            dfs(i,-1,-1);
        }
    }
    for(int i=0;i<m;i++){
        cout << "xy"[ans[i]] << "-+"[ans2[i]] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
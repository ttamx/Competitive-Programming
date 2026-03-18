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
    int n,m,q;
    cin >> n >> m >> q;
    vector<int> deg(n);
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[v].emplace_back(u);
        deg[u]++;
    }
    vector<array<bool,2>> dp(n,{true,false});
    vector<array<int,2>> cnt(n,{0,0});
    for(int i=0;i<n;i++){
        for(int j=0;j<2;j++){
            if(dp[i][j]){
                for(auto k:adj[i]){
                    cnt[k][j^1]++;
                }
            }
        }
    }
    while(q--){
        int op,s;
        cin >> op >> s;
        s--;
        if(op==1){
            queue<tuple<int,int,bool>> qu;
            qu.emplace(s,0,false);
            qu.emplace(s,1,true);
            while(!qu.empty()){
                auto [u,i,f]=qu.front();
                qu.pop();
                if(f==dp[u][i])continue;
                dp[u][i]=f;
                if(f){
                    for(auto v:adj[u]){
                        if(++cnt[v][i^1]==deg[v]){
                            qu.emplace(v,i^1,false);
                        }
                    }
                }else{
                    for(auto v:adj[u]){
                        qu.emplace(v,i^1,true);
                    }
                }
            }
        }else{
            cout << (dp[s][0]?"YES":"NO") << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
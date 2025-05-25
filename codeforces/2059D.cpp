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
    int n,m1,m2,s1,s2;
    cin >> n >> s1 >> s2;
    s1--,s2--;
    vector<vector<int>> adj1(n),adj2(n);
    set<pair<int,int>> e;
    vector<bool> good(n);
    cin >> m1;
    for(int i=0;i<m1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj1[u].emplace_back(v);
        adj1[v].emplace_back(u);
        e.emplace(minmax(u,v));
    }
    cin >> m2;
    for(int i=0;i<m2;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj2[u].emplace_back(v);
        adj2[v].emplace_back(u);
        if(e.count(minmax(u,v))){
            good[u]=true;
            good[v]=true;
        }
    }
    using T = tuple<ll,int,int>;
    priority_queue<T,vector<T>,greater<T>> pq;
    vector<vector<ll>> dp(n,vector<ll>(n,LINF));
    pq.emplace(0LL,s1,s2);
    while(!pq.empty()){
        auto [d,u1,u2]=pq.top();
        pq.pop();
        if(d>dp[u1][u2])continue;
        if(u1==u2&&good[u1]){
            cout << d << "\n";
            return;
        }
        for(auto v1:adj1[u1]){
            for(auto v2:adj2[u2]){
                ll nd=d+abs(v1-v2);
                if(nd<dp[v1][v2]){
                    dp[v1][v2]=nd;
                    pq.emplace(nd,v1,v2);
                }
            }
        }
    }
    cout << -1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
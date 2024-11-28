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
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        adj[p-1].emplace_back(i);
    }
    auto dfs=[&](auto &&self,int u,int p)->int{
        priority_queue<int,vector<int>,greater<int>> pq;
        for(auto v:adj[u]){
            pq.emplace(self(self,v,u));
        }
        if(pq.empty())return 0;
        if(pq.size()==1)return pq.top()+1;
        while(pq.size()>=2){
            int x=pq.top();pq.pop();
            int y=pq.top();pq.pop();
            pq.emplace(max(x,y)+1);
        }
        return pq.top();
    };
    cout << dfs(dfs,0,-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
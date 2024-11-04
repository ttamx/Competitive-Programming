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
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
        x--;
    }
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<n;i++){
        if(b[i]>i){
            adj[i].emplace_back(b[i],a[i]);
        }
        if(i>0){
            adj[i].emplace_back(i-1,0);
        }
    }
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    vector<ll> dp(n,LINF);
    dp[0]=0LL;
    pq.emplace(0LL,0);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dp[u])continue;
        for(auto [v,w]:adj[u]){
            if(d+w<dp[v]){
                dp[v]=d+w;
                pq.emplace(d+w,v);
            }
        }
    }
    ll ans=0LL,sum=0LL;
    for(int i=0;i<n;i++){
        sum+=a[i];
        ans=max(ans,sum-dp[i]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
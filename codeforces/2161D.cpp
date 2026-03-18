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
    vector<vector<int>> pos(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        pos[n-x].emplace_back(i);
    }
    int ans=0;
    vector<pair<int,int>> pre;
    pre.emplace_back(-1,0);
    for(auto &v:pos){
        vector<pair<int,int>> cur;
        cur.emplace_back(-1,0);
        int idx=0,mx=0,dp=-INF;
        for(auto x:v){
            while(idx<pre.size()&&pre[idx].first<=x){
                mx=max(mx,pre[idx].second);
                idx++;
            }
            dp=max(dp,mx)+1;
            ans=max(ans,dp);
            cur.emplace_back(x,dp);
        }
        while(idx<pre.size()){
            mx=max(mx,pre[idx].second);
            idx++;
        }
        cur[0].second=mx;
        pre=move(cur);
    }
    cout << n-ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
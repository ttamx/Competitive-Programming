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
    vector<ll> a(n);
    set<int> s;
    for(auto &x:a){
        cin >> x;
        s.emplace(x);
    }
    ll mx=*max_element(a.begin(),a.end());
    map<ll,int> dp;
    dp[1]=0;
    for(auto x:a){
        auto ndp=dp;
        for(auto [v,c]:dp){
            ll val=lcm(v,x);
            if(val>mx){
                cout << n << "\n";
                return;
            }
            ndp[val]=max(ndp[val],c+1);
        }
        swap(dp,ndp);
    }
    int ans=0;
    for(auto [v,c]:dp){
        if(!s.count(v)){
            ans=max(ans,c);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> b;
    for(auto x:a){
        if(b.empty()||b.back().back()>=x){
            b.push_back({x});
        }else{
            b.back().emplace_back(x);
        }
    }
    int m=b.size();
    vector<pair<int,int>> dp(m);
    vector<int> s(m);
    dp[0]={0,b[0].back()};
    for(int i=1;i<m;i++){
        s[i]=b[i].size();
        int mn=b[i][0],mx=b[i].back();
        auto [cnt,last]=dp[i-1];
        dp[i]={cnt+1,last+s[i]};
        if(last<mn){
            dp[i]=min(dp[i],make_pair(cnt,mx));
        }else{
            dp[i]=min(dp[i],make_pair(cnt+1,mx));
        }
        if(i>=3){
            tie(cnt,last)=dp[i-3];
            dp[i]=min(dp[i],make_pair(cnt+2,min(mx,last+s[i]+s[i-1]+s[i-2])));
        }
    }
    cout << dp.back().first << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
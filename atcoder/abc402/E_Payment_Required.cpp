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
const db EPS=1e-10;
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
    vector<tuple<int,int,int>> a(n);
    for(auto &[s,c,p]:a)cin >> s >> c >> p;
    vector<vector<double>> dp(1<<n,vector<double>(m+1));
    for(int mask=1;mask<1<<n;mask++){
        for(int i=0;i<n;i++){
            if(!(mask>>i&1))continue;
            auto [s,c,p]=a[i];
            double pp=p*0.01;
            int mask2=mask^(1<<i);
            auto cur=dp[mask2];
            for(int j=c;j<=m;j++)cur[j]=max(cur[j],cur[j-c]*(1-pp)+(dp[mask2][j-c]+s)*pp);
            for(int j=0;j<=m;j++)dp[mask][j]=max(dp[mask][j],cur[j]);
        }
    }
    cout << fixed << setprecision(20) << *max_element(dp.back().begin(),dp.back().end()) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
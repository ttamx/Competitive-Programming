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

const int S=1005;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<vector<int>> adj(n);
    vector<int> dep(n),cnt(n),deg(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        p--;
        dep[i]=dep[p]+1;
        cnt[dep[i]]++;
        deg[p]++;
    }
    int d=n;
    for(int i=0;i<n;i++){
        if(!deg[i]){
            d=min(d,dep[i]);
        }
    }
    bitset<S> dp;
    dp[0]=1;
    int sum=0;
    int ans=0;
    for(int i=0;i<=d;i++){
        sum+=cnt[i];
        dp|=dp<<cnt[i];
        for(int j=k;j>=0&&sum-j<=n-k;j--){
            if(dp[j]){
                ans=i+1;
                break;
            }
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
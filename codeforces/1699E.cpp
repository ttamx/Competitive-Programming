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
    vector<bool> seen(m+1);
    int mn=m;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        seen[x]=true;
        mn=min(mn,x);
    }
    vector<int> cnt(m+1),dp(m+1,m);
    for(int i=1;i<=m;i++){
        if(seen[i]){
            cnt[m]++;
        }
    }
    auto update=[&](int i,int v){
        if(v<dp[i]){
            if(seen[i]){
                cnt[dp[i]]--;
            }
            dp[i]=v;
            if(seen[i]){
                cnt[dp[i]]++;
            }
        }
    };
    int mx=m,ans=m;
    for(int i=m;i>=1;i--){
        update(i,i);
        for(int j=1;i*j<=m;j++){
            update(i*j,dp[j]);
        }
        while(cnt[mx]==0){
            mx--;
        }
        if(i<=mn){
            ans=min(ans,mx-i);
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
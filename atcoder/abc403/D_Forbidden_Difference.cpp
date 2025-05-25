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

const int N=1e6+5;

int cnt[N];
int dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,d;
    cin >> n >> d;
    int uniq=0;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        cnt[x]++;
        if(cnt[x]==1)uniq++;
    }
    if(d==0){
        cout << n-uniq << "\n";
        exit(0);
    }
    for(int i=N-1;i>=0;i--){
        dp[i]=cnt[i];
        if(i+2*d<N)dp[i]+=dp[i+2*d];
        if(i+d<N)dp[i]=max(dp[i],dp[i+d]);
    }
    int ans=n;
    for(int i=0;i<d;i++)ans-=dp[i];
    cout << ans << "\n";
}
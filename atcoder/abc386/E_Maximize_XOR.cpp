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

const int N=2e5+5;

int n,k;
ll a[N];
ll ans,cur;

void solve(int cnt,int idx){
    if(cnt==k){
        ans=max(ans,cur);
        return;
    }
    for(int i=idx;i<n&&cnt+n-i>=k;i++){
        cur^=a[i];
        solve(cnt+1,idx+1);
        cur^=a[i];
    }
}

void runcase(){
    cin >> n >> k;
    ll sum=0;
    for(int i=0;i<n;i++){
        cin >> a[i];
        sum^=a[i];
    }
    if(k>n-k){
        k=n-k;
        cur=sum;
    }
    solve(0,0);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
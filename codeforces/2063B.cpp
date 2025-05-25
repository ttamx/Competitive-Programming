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
    int n,l,r;
    cin >> n >> l >> r;
    l--,r--;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    ll base=0;
    for(int i=l;i<=r;i++){
        base+=a[i];
    }
    ll ans=base;
    sort(a.begin(),a.begin()+l);
    sort(a.begin()+l,a.begin()+r+1,greater<int>());
    sort(a.begin()+r+1,a.end());
    ll cur=base;
    for(int i=0,j=l;i<l&&j<=r;i++,j++){
        cur+=a[i]-a[j];
        ans=min(ans,cur);
    }
    cur=base;
    for(int i=r+1,j=l;i<n&&j<=r;i++,j++){
        cur+=a[i]-a[j];
        ans=min(ans,cur);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    ll h,k;
    cin >> n >> h >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    auto b=a;
    for(int i=n-2;i>=0;i--)b[i]=max(b[i],b[i+1]);
    ll ans=0;
    ll tot=accumulate(a.begin(),a.end(),0LL);
    ll t=h/tot;
    ans+=t*(n+k);
    h%=tot;
    if(!h){
        cout << ans-k << "\n";
        return;
    }
    int mn=INF;
    for(int i=0;i<n;i++){
        ans++;
        h-=a[i];
        mn=min(mn,a[i]);
        if(h<=0||h+mn<=b[i+1]){
            cout << ans << "\n";
            return;
        }
    }
    assert(false);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
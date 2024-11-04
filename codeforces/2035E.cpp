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
    ll x,y,z,k;
    cin >> x >> y >> z >> k;
    ll ans=LINF;
    for(ll v=1;v*v<=z;v++){
        ll t=v/k;
        ll cur=t*(t+1)/2*k;
        ll cost=v*x+t*y;
        ll rem=z-cur;
        if(rem>0){
            cost+=((rem-1)/v+1)*y;
        }
        ans=min(ans,cost);
    }
    for(ll c=0;c*c<=z;c++){
        auto check=[&](ll v){
            ll t=v/k;
            ll cur=t*(t+1)/2*k;
            return cur+v*c>=z;
        };
        ll l=1,r=z+k;
        while(l<r){
            ll m=(l+r)/2;
            if(check(m))r=m;
            else l=m+1;
        }
        ll t=l/k;
        ll cur=t*(t+1)/2*k;
        ll cost=l*x+t*y;
        ans=min(ans,cost+c*y);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
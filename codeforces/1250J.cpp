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
    ll n,k;
    cin >> n >> k;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    auto check=[&](ll mid){
        ll rem=0,cur=0;
        for(auto x:a){
            if(x+rem>=mid)x-=mid-rem,cur++;
            cur+=x/mid;
            rem=x%mid;
        }
        return cur>=k;
    };
    ll l=0,r=accumulate(a.begin(),a.end(),0LL)/k;
    while(l<r){
        ll mid=(l+r+1)/2;
        if(check(mid))l=mid;
        else r=mid-1;
    }
    cout << l*k << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
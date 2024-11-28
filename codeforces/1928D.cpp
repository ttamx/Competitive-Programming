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
    ll b,c;
    cin >> n >> b >> c;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    sort(a.rbegin(),a.rend());
    ll ans=0,base=0;
    for(int k=1;k<=a[0];k++){
        ll cur=0;
        for(auto x:a){
            if(x<k)break;
            if(x==k){
                base+=x*(x-1)/2;
                continue;
            }
            ll q=x/k;
            ll r=x%k;
            cur+=q*q*k*(k-1)/2;
            cur+=r*(r-1)/2;
            cur+=q*r*(r-1);
            cur+=q*r*(k-r);
        }
        cur+=base;
        ans=max(ans,cur*b-(k-1)*c);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
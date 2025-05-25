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
    ll n,m;
    cin >> n >> m;
    if((n^m)<n){
        cout << 1 << "\n";
        cout << n << " " << m << "\n";
        return;
    }
    int a=60;
    while(a>=0&&(n>>a&1)==0){
        a--;
    }
    a--;
    while(a>=0&&(n>>a&1)==0){
        a--;
    }
    int b=60;
    while(b>=0&&(m>>b&1)==0){
        b--;
    }
    if(b>a){
        cout << -1 << "\n";
        return;
    }
    ll k=(2LL<<a)-1;
    cout << 2 << "\n";
    cout << n << " " << k << " " << m << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
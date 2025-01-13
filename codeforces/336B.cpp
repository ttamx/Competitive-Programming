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
    ll m,r;
    cin >> m >> r;
    db ans=2*r*m;
    for(ll i=1;i<m;i++){
        if(i==1){
            ans+=(m-i)*2*(i*r*2+sqrtl(2*r*r));
        }else{
            ans+=(m-i)*2*((i-1)*r*2+sqrtl(8*r*r));
        }
    }
    cout << ans/(m*m) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(12);
    int t(1);
    while(t--)runcase();
}
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
    cin >> n;
    map<int,int> m1,m2;
    for(int i=0;i<n;i++){
        int x,y;
        cin >> x >> y;
        m1[x+y]++;
        m2[x]++;
    }
    bool ok=false;
    int v1=0,v2=0;
    for(auto [v,c]:m1){
        if(c%2==1){
            assert(!ok);
            v1=v;
            ok=true;
        }
    }
    assert(ok);
    ok=false;
    for(auto [v,c]:m2){
        if(c%2==1){
            assert(!ok);
            v2=v;
            ok=true;
        }
    }
    assert(ok);
    cout << v2 << " " << v1-v2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
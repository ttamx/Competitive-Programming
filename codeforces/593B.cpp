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
    ll st,ed;
    cin >> st >> ed;
    vector<pair<ll,ll>> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    auto eval=[&](pair<ll,ll> e,ll x){
        return x*e.first+e.second;
    };
    sort(a.begin(),a.end(),[&](pair<ll,ll> x,pair<ll,ll> y){
        return make_pair(eval(x,st),x.first)<make_pair(eval(y,st),y.first);
    });
    auto b=a;
    sort(b.begin(),b.end(),[&](pair<ll,ll> x,pair<ll,ll> y){
        return make_pair(eval(x,ed),-x.first)<make_pair(eval(y,ed),-y.first);
    });
    cout << (a==b?"NO":"YES") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
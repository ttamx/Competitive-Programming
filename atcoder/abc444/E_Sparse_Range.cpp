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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,d;
    cin >> n >> d;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    multiset<int> ms;
    auto check=[&](int x){
        auto it=ms.lower_bound(x);
        if(it!=ms.end()&&*it-x<d)return false;
        if(it!=ms.begin()&&x-*prev(it)<d)return false;
        return true;
    };
    ll ans=0;
    for(int i=0,j=0;i<n;i++){
        while(!check(a[i]))ms.erase(ms.find(a[j++]));
        ms.emplace(a[i]);
        ans+=i-j+1;
    }
    cout << ans << "\n";
}
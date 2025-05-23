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
    vector<int> a(n),p(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:p){
        cin >> x;
        x--;
    }
    ll ans=0,ans2=0;
    multiset<ll> cur,cand;
    for(auto x:a){
        cand.emplace(x);
    }
    for(int k=0;k*2+1<=n;k++){
        while(cur.size()<k+1){
            cur.emplace(*cand.rbegin());
            cand.erase(prev(cand.end()));
        }
        ll res=1LL*(k+1)*(*cur.begin());
        if(res>ans){
            ans=res;
            ans2=k+1;
        }
        if(cur.count(a[p[k]])){
            cur.erase(cur.find(a[p[k]]));
        }else{
            cand.erase(cand.find(a[p[k]]));
        }
    }
    cout << ans << " " << ans2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
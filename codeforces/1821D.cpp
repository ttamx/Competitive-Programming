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
    int n,k;
    cin >> n >> k;
    vector<int> l(n),r(n);
    for(auto &x:l)cin >> x;
    for(auto &x:r)cin >> x;
    ll ans=LINF;
    ll cur=0,base=0;
    ll single=0;
    for(int i=0;i<n;i++){
        ll sz=r[i]-l[i]+1;
        if(cur+single+sz>=k){
            ans=min(ans,l[i]+base+2+2*max(0LL,k-cur-sz)+max(0LL,min(k-cur,sz)-1));
        }
        if(sz==1){
            single++;
        }else{
            cur+=sz;
            base+=2;
        }
    }
    cout << (ans<LINF?ans:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
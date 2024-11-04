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
    ll l,r,n,k;
    cin >> l >> r >> n >> k;
    auto calc=[&](ll x){
        ll res=0;
        {
            ll v=x%4;
            if(v==1||v==2){
                res^=1;
            }
        }
        for(int i=1;i<60;i++){
            ll b=1LL<<i;
            ll v=x%(b*2);
            if(v>=b){
                res^=((v&1)^1)<<i;
            }
        }
        return res;
    };
    auto calc2=[&](ll x){
        if(k>x){
            return 0LL;
        }
        ll l=0,r=x>>n;
        while(l<r){
            ll m=(l+r+1)/2;
            ll v=(m<<n)|k;
            if(v<=x){
                l=m;
            }else{
                r=m-1;
            }
        }
        ll res=0;
        if(l%2==0){
            res^=k;
        }
        res^=calc(l)<<n;
        return res;
    };
    ll ans=calc(r)^calc(l-1);
    ans^=calc2(r)^calc2(l-1);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
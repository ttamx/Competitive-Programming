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
    ll n,k,s,m;
    cin >> n >> k >> s >> m;
    if(m==1){
        for(int i=0;i<=k;i++){
            ll t=k-i;
            ll lo=2*t;
            ll hi=n*t;
            if(lo<=s&&s<=hi)return void(cout << i << "\n");
            s-=m;
        }
    }else if(m==n){
        for(int i=0;i<=k;i++){
            ll t=k-i;
            ll lo=t;
            ll hi=n*t-t;
            if(lo<=s&&s<=hi)return void(cout << i << "\n");
            s-=m;
        }
    }else{
        for(int i=0;i<=k;i++){
            ll t=k-i;
            ll lo=m*t+t;
            ll u=max(0LL,(lo-s+m-1)/m);
            lo-=m*u;
            ll hi=n*t+(m-n-1)*u;
            if(lo<=s&&s<=hi)return void(cout << i << "\n");
            s-=m;
        }
    }
    assert(false);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
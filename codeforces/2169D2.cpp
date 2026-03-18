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

using i128 = __int128_t;

const ll L = 1e12;
const i128 P = 1791764773657LL;

const int N=100;

i128 inv[N];

ll floor(ll a,ll b){
    return a/b-((a^b)<0&&a%b);
}

void runcase(){
    ll x,y,k;
    cin >> x >> y >> k;
    auto calc=[&](i128 v)->i128 {
        if(y==1)return i128(0);
        i128 res=v,cur=v,coef=1;
        for(int i=1;i<=x;i++){
            cur=-floor(cur,y);
            if(cur==0)break;
            coef=coef*(x-i+1)%P;
            coef=coef*inv[i]%P;
            res=(res+coef*cur%P+P)%P;
        }
        cerr << (ll)v << " : " << (ll)res << "\n";
        return res;
    };
    ll l=1,r=L+1;
    while(l<r){
        ll m=(l+r)/2;
        if(calc(m)>=k)r=m;
        else l=m+1;
    }
    cerr << "-----\n";
    cout << (l>L?-1LL:l) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cerr << (ll)P << "\n";
    inv[1]=1;
    for(int i=2;i<N;i++){
        inv[i]=P-i128(P/i)*inv[P%i]%P;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}
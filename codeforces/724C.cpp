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

ll euclid(ll a,ll b,ll &x,ll &y){
	if(!b)return x=1,y=0,a;
	ll d=euclid(b,a%b,y,x);
	return y-=a/b*x,d;
}

ll crt(ll a,ll m,ll b,ll n){
	if(n>m)swap(a,b),swap(m,n);
	ll x,y,g=euclid(m,n,x,y);
	if((a-b)%g!=0)return LINF;
	x=(b-a)%n*x%n/g*m+a;
	return x<0?x+m*n/g:x;
}

void runcase(){
    ll n,m,k;
    cin >> n >> m >> k;
    while(k--){
        ll x,y;
        cin >> x >> y;
        ll ans=LINF;
        ans=min(ans,crt(x,2*n,y,2*m));
        ans=min(ans,crt(2*n-x,2*n,y,2*m));
        ans=min(ans,crt(x,2*n,2*m-y,2*m));
        ans=min(ans,crt(2*n-x,2*n,2*m-y,2*m));
        cout << (ans<LINF?ans:-1LL) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
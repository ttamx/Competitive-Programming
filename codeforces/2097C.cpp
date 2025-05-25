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
    if(b==0)return x=1,y=0,a;
    ll d=euclid(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
 
ll crt(ll a, ll m, ll b, ll n) {
	if(n>m)swap(a,b),swap(m,n);
	ll x,y,g=euclid(m,n,x,y);
    if((a-b)%g!=0)return -1;
	x=(b-a)%n*x%n/g*m+a;
	return x<0?x+m*n/g:x;
}

void runcase(){
    ll n,sx,sy,vx,vy;
    cin >> n >> sx >> sy >> vx >> vy;
    ll vg=gcd(vx,vy);
    vx/=vg,vy/=vg;
    ll x=n-sx,y=n-sy;
    ll x1,y1,tmp;
    ll gx=euclid(vx,n,x1,tmp);
    if(x%gx!=0)return void(cout << "-1\n");
    ll nx=n/gx;
    if(x1<0)x1+=nx;
    ll gy=euclid(vy,n,y1,tmp);
    if(y%gy!=0)return void(cout << "-1\n");
    ll ny=n/gy;
    if(y1<0)y1+=ny;
    x1=x1*(x/gx)%nx;
    y1=y1*(y/gy)%ny;
    ll t=crt(x1,nx,y1,ny);
    if(t==-1)return void(cout << "-1\n");
    ll dx=(vx*t+sx)/n;
    ll dy=(vy*t+sy)/n;
    ll ans=dx+dy-2;
    ans+=(dx+dy)/2;
    ans+=abs(dx-dy)/2;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
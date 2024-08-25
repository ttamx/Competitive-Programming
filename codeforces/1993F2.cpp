#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

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
    ll n,k,w,h;
    cin >> n >> k >> w >> h;
    w*=2,h*=2;
    string s;
    cin >> s;
    ll dx=0,dy=0;
    map<pair<ll,ll>,ll> cnt;
    for(auto x:s){
        if(x=='L')dx--;
        if(x=='R')dx++;
        if(x=='U')dy++;
        if(x=='D')dy--;
        if(dx<0)dx+=w;
        if(dx>=w)dx-=w;
        if(dy<0)dy+=h;
        if(dy>=h)dy-=h;
        cnt[{dx,dy}]++;
    }
    ll ans=0;
    for(auto [xy,v]:cnt){
        auto [x,y]=xy;
        x=(w-x)%w;
        y=(h-y)%h;
        ll x1,y1,tmp;
        ll gx=euclid(dx,w,x1,tmp);
        if(x%gx!=0)continue;
        ll w1=w/gx;
        if(x1<0)x1+=w1;
        ll gy=euclid(dy,h,y1,tmp);
        if(y%gy!=0)continue;
        ll h1=h/gy;
        if(y1<0)y1+=h1;
        x1=x1*(x/gx)%w1;
        y1=y1*(y/gy)%h1;
        ll t=crt(x1,w1,y1,h1);
        if(t==-1)continue;
        ll l=lcm(w1,h1);
        if(k>t)ans+=((k-t-1)/l+1)*v;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
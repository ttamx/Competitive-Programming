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

struct Line{
	mutable ll m,c,p;
	Line(ll m,ll c):m(m),c(c),p(0){}
	bool operator<(const Line &o)const{return m>o.m;}
	bool operator<(const ll &o)const{return p<o;}
};
 
struct LineContainer:multiset<Line,less<>>{
    ll div(ll a,ll b){return a/b-(a%b&&(a^b)<0);}
	bool isect(iterator x,iterator y){
		if(y==end())return x->p=LINF,false;
		if(x->m==y->m)x->p=x->c<=y->c?LINF:-LINF;
		else x->p=div(x->c-y->c,y->m-x->m);
		return x->p>=y->p;
	}
	void add_line(ll m,ll c){
		auto x=insert(Line(m,c)),y=x;
		while(isect(x,next(x)))erase(next(x));
		if(x!=begin()&&isect(--x,y))isect(x,erase(y));
		while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
	}
	ll query(ll x){
		if(empty())return LINF;
		auto l=*lower_bound(x);
		return l.m*x+l.c;
	}
};

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    vector<ll> dp(n+1);
    LineContainer cht1,cht2;
    cht1.add_line(0,0);
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1]+a[i];
        dp[i]=min(dp[i],cht1.query(a[i])+i-1+a[i]*i);
        dp[i]=min(dp[i],cht2.query(i)+i*2-1);
        cht2.add_line(a[i],cht1.query(a[i])-i);
        cht1.add_line(-i,dp[i]-i);
        cout << dp[i] << " \n"[i==n];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
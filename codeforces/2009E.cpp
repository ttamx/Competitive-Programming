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

void runcase(){
    ll n,k;
    cin >> n >> k;
    auto f=[&](ll x){
        ll res=0;
        res+=(2*k+x-1)*x/2;
        res-=(2*k+x+n-1)*(n-x)/2;
        return abs(res);
    };
    ll l=1,r=n;
    while(l<r){
        ll m=(l+r)/2;
        if(f(m)>f(m+1))l=m+1;
        else r=m;
    }
    cout << f(l) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
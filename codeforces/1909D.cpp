#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
    int n;
    ll k;
    cin >> n >> k;
    vl a(n);
    for(auto &x:a)cin >> x;
    if(*max_element(all(a))==*min_element(all(a)))return void(cout << "0\n");
    ll g=0,mul=1;
    for(auto x:a){
        if(x<k)mul=-1;
        g=gcd(g,x-k);
    }
    g*=mul;
    ll ans=0;
    for(auto x:a){
        ll res=(x-k)/g-1;
        if(g+k<0||res<0)return void(cout << "-1\n");
        ans+=res;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
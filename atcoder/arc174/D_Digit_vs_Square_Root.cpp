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

using i128 = __int128_t;

void runcase(){
    ll n;
    cin >> n;
    ll ans=1;
    for(i128 x=10;;x*=10){
        i128 v=(x-1)*(x-1)-1;
        if(v>n)break;
        ans++;
    }
    for(i128 x=10;;x*=10){
        i128 v=x*(x-1);
        if(v>n)break;
        ans+=min((i128)n,x*x-1)-v+1;
    }
    for(i128 x=10;;x*=10){
        i128 v=x*x;
        if(v>n)break;
        ans+=min((i128)n,x*(x+1)-1)-v+1;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
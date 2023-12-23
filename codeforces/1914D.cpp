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

ll solve(const vl &a,const vl &b,const vl &c){
    ll sa=0,sb=0,sc=0;
    int n=sz(a);
    for(int i=0;i<n;i++){
        sc=max(sc,sb+c[i]);
        sb=max(sb,sa+b[i]);
        sa=max(sa,a[i]);
    }
    return sc;
}

void runcase(){
    int n;
    cin >> n;
    vl a(n),b(n),c(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    for(auto &x:c)cin >> x;
    ll ans=0;
    ans=max(ans,solve(a,b,c));
    ans=max(ans,solve(a,c,b));
    ans=max(ans,solve(b,a,c));
    ans=max(ans,solve(b,c,a));
    ans=max(ans,solve(c,a,b));
    ans=max(ans,solve(c,b,a));
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
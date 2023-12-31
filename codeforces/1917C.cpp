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
    int n,m,d;
    cin >> n >> m >> d;
    vi a(n),b(m);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    ll ans=(d-1)/2;
    for(int i=1;i<=n;i++)if(a[i-1]==i)ans++;
    for(int i=1;i<=min(2*n+10,d-1);i++){
        for(int j=0;j<b[(i-1)%m];j++)a[j]++;
        ll tmp=0;
        for(int j=1;j<=n;j++)if(a[j-1]==j)tmp++;
        ans=max(ans,tmp+(d-i-1)/2);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
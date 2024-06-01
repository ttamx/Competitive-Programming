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
    int n,k;
    cin >> n >> k;
    vl a(n+2),b(n+2);
    for(int i=1;i<=n;i++)cin >> a[i],a[i]+=a[i-1];
    for(int i=1;i<=n;i++)cin >> b[i],b[i]+=b[i-1];
    vl dp(n+1);
    for(int i=1;i<=n;i++)dp[i]=min(a[i],b[i]);
    for(int s=2;s<=k;s++){
        vl ndp(n+1);
        ll mna=LINF,mnb=LINF;
        for(int i=s;i<=n;i++){
            mna=min(mna,dp[i-1]-a[i-1]);
            mnb=min(mnb,dp[i-1]-b[i-1]);
            ndp[i]=min(mna+a[i],mnb+b[i]);
        }
        swap(dp,ndp);
    }
    cout << dp[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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

const int N=3e5+5;

int n;
ll c;
ll a[N],qs[N];
ll ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> c;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+a[i];
    ans=qs[n];
    ll res=0;
    if(c>1){
        ll mn=0;
        for(int i=1;i<=n;i++){
            res=max(res,qs[i]-mn);
            mn=min(mn,qs[i]);
        }
        res*=c-1;
    }
    if(c<1){
        ll mx=0;
        for(int i=1;i<=n;i++){
            res=min(res,qs[i]-mx);
            mx=max(mx,qs[i]);
        }
        res*=c-1;
    }
    ans+=res;
    cout << ans;
}
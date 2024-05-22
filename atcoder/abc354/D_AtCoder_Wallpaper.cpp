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

const int OFF=1e9;

ll calc0(ll x){
    if(x==0)return 0;
    if(x==1)return 2;
    if(x<=3)return 3;
    return (x/4)*4+calc0(x%4);
}

ll calc1(ll x){
    if(x==0)return 0;
    if(x==1)return 1;
    if(x==2)return 3;
    if(x==3)return 4;
    return (x/4)*4+calc1(x%4);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll a,b,c,d;
    cin >> a >> b >> c >> d;
    a+=OFF;
    c+=OFF;
    ll ans=(calc0(c)-calc0(a)+calc1(c)-calc1(a))*((d-b)/2);
    if((d-b)%2){
        if(b%2==0)ans+=calc0(c)-calc0(a);
        else ans+=calc1(c)-calc1(a);
    }
    cout << ans;
}
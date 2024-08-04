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

struct Sieve{
    int n;
    vi lp,prime;
    Sieve(){}
    void init(int _n){
        n=_n;
        lp.assign(n+1,0);
        for(int i=2;i<=n;i++){
            if(lp[i]==0){
                lp[i]=i;
                prime.emplace_back(i);
                for(ll j=1ll*i*i;j<=n;j+=i)if(lp[j]==0)lp[j]=i;
            }
        }
    }
}sieve;

const int LIM=1e5;

int fsqrt(ll x,ll l,ll r){
    while(l<r){
        ll m=(l+r+1)/2;
        if(m*m>x)r=m-1;
        else l=m;
    }
    return l;
}

void runcase(){
    ll n;
    cin >> n;
    n-=4;
    for(ll x:sieve.prime){
        if(x==2)continue;
        ll y=n-x*x;
        if(x*x>=y)break;
        ll z=fsqrt(y,x+1,LIM);
        if(sieve.lp[z]==z&&z*z==y)return void(cout << "Yes\n");
    }
    cout << "No\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    sieve.init(100000);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
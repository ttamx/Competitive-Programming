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
const db EPS=1e-18;
const db PI=acos(db(-1));

void runcase(){
    int n;
    db p,q;
    cin >> n >> p >> q;
    vector<db> a(n),b(n);
    for(int i=0;i<n;i++)cin >> a[i] >> b[i];
    db mn=1;
    for(int i=0;i<n;i++)mn=min(mn,db(1)/a[i]);
    db l=0,r=mn;
    auto calc=[&](db x){
        db y=1;
        for(int i=0;i<n;i++)y=min(y,(1-a[i]*x)/b[i]);
        return p*x+q*y;
    };
    while(r-l>EPS){
        db m1=l+(r-l)/3;
        db m2=r-(r-l)/3;
        if(calc(m1)>calc(m2))r=m2;
        else l=m1;
    }
    cout << fixed << setprecision(15);
    cout << calc((l+r)/2) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
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
    int h,n;
    cin >> h >> n;
    vl a(n),c(n);
    for(auto &x:a)cin >> x;
    for(auto &x:c)cin >> x;
    ll l=1,r=4e10+100;
    while(l<r){
        ll m=(l+r)/2;
        ll hp=h;
        for(int i=0;i<n;i++){
            hp-=((m-1)/c[i]+1)*a[i];
            if(hp<=0)break;
        }
        if(hp<=0)r=m;
        else l=m+1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
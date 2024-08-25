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
    int n;
    cin >> n;
    vector<pair<ll,ll>> p(n);
    for(auto &[x,y]:p)cin >> x >> y;
    ll x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;
    ll dx=x2-x1,dy=y2-y1;
    ll d=dx*dx+dy*dy;
    for(auto [x,y]:p){
        ll dx2=x2-x,dy2=y2-y;
        ll d2=dx2*dx2+dy2*dy2;
        if(d2<=d){
            return void(cout << "NO\n");
        }
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
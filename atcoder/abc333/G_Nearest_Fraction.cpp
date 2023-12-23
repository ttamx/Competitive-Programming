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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    db r;
    ll n;
    cin >> r >> n;
    db d=1-r;
    ll x=1,y=1;
    auto solve=[&](ll p,ll q){
        db dr=abs(r-(db(p)/q));
        if(dr<d){
            d=dr,x=p,y=q;
        }else if(dr==d&&db(x)/y>db(p)/q){
            x=p,y=q;
        }
    };
    solve(0,1);
    ll pl=0,ql=1,pr=1,qr=1;
    while(true){
        ll pm=pl+pr,qm=ql+qr;
        ll g=gcd(pm,qm);
        pm/=g,qm/=g;
        if(qm>n)break;
        solve(pm,qm);
        if(r*qm<=pm)pr=pm,qr=qm;
        else pl=pm,ql=qm;
    }
    cout << x << " " << y;
}
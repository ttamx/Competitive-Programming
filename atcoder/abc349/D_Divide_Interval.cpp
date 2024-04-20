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

ll x,y;
vector<pll> ans;

void solve(ll l,ll r){
    if(y<=l||r<=x)return;
    if(x<=l&&r<=y){
        ans.emplace_back(l,r);
        return;
    }
    ll m=(l+r)/2;
    solve(l,m);
    solve(m,r);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> x >> y;
    solve(0LL,1LL<<60);
    cout << sz(ans) << "\n";
    for(auto [l,r]:ans)cout << l << " " << r << "\n";
}
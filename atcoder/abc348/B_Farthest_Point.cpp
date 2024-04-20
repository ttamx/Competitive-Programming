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

ll calc(pll a,pll b){
    ll x=a.first-b.first;
    ll y=a.second-b.second;
    return x*x+y*y;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pll> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    for(int i=0;i<n;i++){
        pll res(0,0);
        for(int j=0;j<n;j++)res=max(res,pll(calc(a[i],a[j]),-j));
        cout << -res.second+1 << "\n";
    }
}
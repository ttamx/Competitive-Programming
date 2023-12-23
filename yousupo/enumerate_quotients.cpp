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
    ll n;
    cin >> n;
    ll d=1;
    vl ans;
    while(n/d>0){
        ll val=n/d;
        ans.emplace_back(val);
        d++;
        if(n/d==val)n=d*(val-1);

    }
    reverse(ans.begin(),ans.end());
    cout << sz(ans) << "\n";
    for(auto x:ans)cout << x << " ";
}
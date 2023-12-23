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
const int MOD=1000000007;
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

void runcase(){
    int n;
    cin >> n;
    vl l(n),c(n);
    set<ll> r;
    for(auto &x:l)cin >> x;
    for(int i=0;i<n;i++){
        ll x;
        cin >> x;
        r.emplace(x);
    }
    for(auto &x:c)cin >> x;
    sort(l.rbegin(),l.rend());
    sort(all(c));
    vl d;
    for(auto x:l){
        auto it=r.upper_bound(x);
        d.emplace_back(*it-x);
        r.erase(it);
    }
    sort(d.rbegin(),d.rend());
    ll ans=0;
    for(int i=0;i<n;i++)ans+=c[i]*d[i];
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    int a,b,c,d,e,f;
    cin >> a >> b >> c >> d >> e >> f;
    int ans=0;
    set<pii> s,t;
    for(auto x:{-1,1})for(auto y:{-1,1})s.emplace(c+a*x,d+b*y);
    for(auto x:{-1,1})for(auto y:{-1,1})s.emplace(c+b*x,d+a*y);
    for(auto x:{-1,1})for(auto y:{-1,1})t.emplace(e+a*x,f+b*y);
    for(auto x:{-1,1})for(auto y:{-1,1})t.emplace(e+b*x,f+a*y);
    for(auto x:t)if(s.count(x))ans++;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
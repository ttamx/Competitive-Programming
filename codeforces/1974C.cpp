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
    vi a(n);
    for(auto &x:a)cin >> x;
    map<pair<int,int>,int> mp[3];
    map<tuple<int,int,int>,int> mp2;
    ll ans=0;
    for(int i=2;i<n;i++){
        int x=a[i-2],y=a[i-1],z=a[i];
        ans+=mp[0][{x,y}]++;
        ans+=mp[1][{x,z}]++;
        ans+=mp[2][{y,z}]++;
        ans-=3*mp2[{x,y,z}]++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
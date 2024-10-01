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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<ll> a(n+1);
    map<int,ll> mp;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        mp[a[i]];
    }
    for(auto &[x,y]:mp){
        y=rng();
    }
    for(int i=1;i<=n;i++){
        a[i]=a[i-1]^mp[a[i]];
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        cout << ((a[r]^a[l-1])==0?"YES":"NO") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
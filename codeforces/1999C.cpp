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
    int n,s,m;
    cin >> n >> s >> m;
    vector<pair<int,int>> a(n);
    for(auto &[l,r]:a)cin >> l >> r;
    sort(a.begin(),a.end());
    int p=0;
    for(auto [l,r]:a){
        if(l-p>=s)return void(cout << "YES\n");
        p=r;
    }
    if(m-p>=s)cout << "YES\n";
    else cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
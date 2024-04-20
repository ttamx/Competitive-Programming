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
    set<int> s;
    s.emplace(-2),s.emplace(n+2);
    for(int i=1;i<=n;i++)if(a[i]!=a[i-1])s.emplace(i);
    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;
        int id=*s.upper_bound(l);
        if(id<=r)cout << id << " " << id+1 << "\n";
        else cout << "-1 -1\n";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
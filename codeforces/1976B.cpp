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
    vector<int> a(n),b(n+1);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    int x=b.back();
    ll ans=0;
    int add=INF;
    for(int i=0;i<n;i++){
        auto [l,r]=minmax(a[i],b[i]);
        ans+=r-l;
        if(l<=x&&x<=r)add=0;
        add=min(add,abs(x-l));
        add=min(add,abs(x-r));
    }
    cout << ans+add+1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    vl a(n);
    for(auto &x:a)cin >> x;
    for(int i=1;i<n;i++)a[i]+=a[i-1];
    int q;
    cin >> q;
    while(q--){
        int l;
        ll u;
        cin >> l >> u;
        l--;
        int r=n-1;
        ll st=l?a[l-1]:0;
        auto calc=[&](int m){
            ll x=a[m]-st;
            return (2*u-x+1)*x/2;
        };
        while(l<r){
            int m=(l+r)/2;
            if(calc(m+1)>calc(m))l=m+1;
            else r=m;
        }
        cout << l+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
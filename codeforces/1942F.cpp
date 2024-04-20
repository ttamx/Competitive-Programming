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

ll sqr(ll x){
    ll l=0,r=INF;
    while(l<r){
        ll m=(l+r+1)/2;
        if(m*m<=x)l=m;
        else r=m-1;
    }
    return l;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vl a(n);
    for(auto &x:a)cin >> x;
    while(q--){
        int k;
        ll x;
        cin >> k >> x;
        a[k-1]=x;
        ll res=0;
        for(int i=max(0,n-100);i<n;i++){
            res=sqr(res+a[i]);
        }
        cout << res << "\n";
    }
}
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
    ll n,q;
    cin >> n >> q;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    for(int i=1;i<n;i++)a[i]+=a[i-1];
    auto query=[&](ll l,ll r){
        if(r<l)return 0LL;
        ll res=a[r];
        if(l>0)res-=a[l-1];
        return res;
    };
    while(q--){
        ll l,r;
        cin >> l >> r;
        l--,r--;
        ll ans=0;
        ll cl=l/n,cr=r/n;
        ll il=l%n,ir=r%n;
        if(cl+il<n){
            ans+=query(cl+il,n-1)+query(0,cl-1);
        }else{
            ans+=query(cl+il-n,cl-1);
        }
        ans+=(cr-cl-1)*query(0,n-1);
        if(cr+ir<n){
            ans+=query(cr,cr+ir);
        }else{
            ans+=query(cr,n-1)+query(0,cr+ir-n);
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
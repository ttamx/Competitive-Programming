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
    int n,q,k;
    cin >> n >> q >> k;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    vector<pair<int,int>> qr(q);
    vector<int> ans(q);
    for(auto &[l,r]:qr){
        cin >> l >> r;
    }
    vector<int> cnt1(n+1),cnt2(n+1);
    for(int v=1;v*v<=k;v++){
        int v2=k/(v+1)+1;
        for(int i=1;i<=n;i++){
            cnt1[i]=cnt1[i-1]+(a[i]<=v);
            cnt2[i]=cnt2[i-1]+(a[i]>=v2);
        }
        for(int i=0;i<q;i++){
            auto [l,r]=qr[i];
            int c1=cnt1[r]-cnt1[l-1];
            int c2=cnt2[r]-cnt2[l-1];
            ans[i]=max(ans[i],min((c2-c1+1)/2,(r-l+1)/2-c1));
        }
    }
    for(int i=0;i<q;i++){
        cout << ans[i] << " \n"[i==q-1];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
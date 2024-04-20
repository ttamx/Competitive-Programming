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
    int n,q;
    cin >> n >> q;
    vl a(n+2),b(n+2);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        a[i]=a[i-1]+(x==1);
        b[i]=b[i-1]+x-1;
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        ll c=a[r]-a[l-1];
        ll d=b[r]-b[l-1];
        cout << (l!=r&&c<=d?"YES":"NO") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
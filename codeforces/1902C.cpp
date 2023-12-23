#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
const int MOD=1000000007;
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

void runcase(){
    int n;
    cin >> n;
    vi a(n);
    for(auto &x:a)cin >> x;
    sort(all(a));
    if(n==1)return void(cout << "1\n");
    if(n==2)return void(cout << "3\n");
    int g=0;
    for(int i=1;i<n;i++)g=gcd(g,a[i]-a[i-1]);
    ll ans=0;
    int mx=a.back();
    for(auto x:a)ans+=(mx-x)/g;
    int add=n;
    for(int i=1;i<n;i++){
        int d=a[i]-a[i-1];
        if(d==g)continue;
        add=min(add,(mx-a[i])/g+1);
    }
    ans+=add;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
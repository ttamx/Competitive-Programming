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
const ll MOD=1e18+9;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

const int N=2e5+5;

using ull = unsigned long long;

const ull BASE=31;

ull pw[N];

void runcase(){
    int n,q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<ull> a(n+2),b(n+2);
    for(int i=1;i<=n;i++)a[i]=a[i-1]+pw[i]*(s[i-1]-'a'+1);
    for(int i=n;i>=1;i--)b[i]=b[i+1]+pw[n-i+1]*(s[i-1]-'a'+1);
    auto geta=[&](int l,int r){
        return (a[r]-a[l-1])*pw[n-l+1];
    };
    auto getb=[&](int l,int r){
        return (b[l]-b[r+1])*pw[r];
    };
    vi eve(n+2),odd(n+2);
    for(int i=2;i<=n;i++)eve[i]=eve[i-1]+(s[i-1]!=s[i-2]);
    for(int i=3;i<=n;i++)odd[i]=odd[i-2]+(s[i-1]!=s[i-3]);
    while(q--){
        int l,r;
        cin >> l >> r;
        ll ans=0;
        if(geta(l,r)!=getb(l,r))ans=r-l+1;
        ll k=r-l;
        if(eve[r]-eve[l]>0)ans+=(k/2)*(k/2+1);
        if(odd[r]-odd[l+1]>0)ans+=((k+1)/2)*((k+1)/2)-1;
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    pw[0]=1;
    for(int i=1;i<N;i++)pw[i]=pw[i-1]*BASE;
    int t(1);
    cin >> t;
    while(t--)runcase();
}
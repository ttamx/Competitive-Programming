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
    vi pre(n),suf(n);
    int l=0;
    for(int i=1;i<n;i++){
        pre[i]=gcd(a[i-1],a[i]);
        if(pre[i]<pre[i-1])break;
        l=i;
    }
    int r=n-1;
    suf[n-1]=INF;
    for(int i=n-2;i>=0;i--){
        suf[i]=gcd(a[i],a[i+1]);
        if(suf[i]>suf[i+1])break;
        r=i;
    }
    if(l>=n-2||r<=1)return void(cout << "YES\n");
    for(int i=1;i<n-1;i++){
        if(l<i-1||i+1<r)continue;
        int val=gcd(a[i-1],a[i+1]);
        if(pre[i-1]<=val&&val<=suf[i+1])return void(cout << "YES\n");
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
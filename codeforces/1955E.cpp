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
    for(auto &x:a){
        char c;
        cin >> c;
        x=c-'0';
    }
    for(int i=n-1;i>=1;i--)a[i]^=a[i-1];
    a[0]^=1;
    for(int k=n;k>=2;k--){
        auto b=a;
        b.emplace_back(0);
        for(int i=0;i<=n-k;i++)b[i+k]^=b[i],b[i]=0;
        b.pop_back();
        if(b==vi(n,0))return void(cout << k << "\n");
    }
    cout << 1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
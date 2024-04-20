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
    string a,b;
    cin >> a >> b;
    int n=sz(a);
    int v=0;
    for(int i=0;i<n;i++)if(a[i]>b[i])swap(a[i],b[i]);
    bool ok=false;
    for(int i=0;i<n;i++){
        if(ok)swap(a[i],b[i]);
        if(a[i]<b[i])ok=true;
    }
    cout << a << "\n";
    cout << b << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
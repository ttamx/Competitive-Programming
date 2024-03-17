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
    int n,k;
    cin >> n >> k;
    int comp=0;
    vi a(n),b(n);
    k=min(n,k);
    for(int i=0;i<n;i+=k,comp++){
        int l=i,r=min(n,i+k)-1;
        int s=r-l+1;
        int m=s/2;
        for(int j=r;j>=l;j--){
            a[j]=i+m++%s;
            b[j]=comp;
        }
    }
    for(auto x:a)cout << x+1 << " ";
    cout << "\n";
    cout << comp << "\n";
    for(auto x:b)cout << x+1 << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    array<int,2> a,b;
    cin >> a[0] >> a[1];
    cin >> b[0] >> b[1];
    int ans=0;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            int cnt=0;
            if(a[i]>b[j])cnt++;
            if(b[j]>a[i])cnt--;
            if(a[i^1]>b[j^1])cnt++;
            if(b[j^1]>a[i^1])cnt--;
            ans+=(cnt>0);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
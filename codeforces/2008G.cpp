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
    int g=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        g=gcd(g,x);
    }
    if(n==1){
        int ans=k-1;
        if(g<=ans)ans++;
        cout << ans << "\n";
        return;
    }
    if(g==0){
        cout << k << "\n";
        return;
    }
    int ans=k-1;
    int cur=0,cnt=0;
    while(cnt<n&&cur<=ans){
        ans++;
        cur+=g;
        cnt++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
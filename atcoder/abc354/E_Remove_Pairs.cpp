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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    int m=1<<n;
    vi a(n),b(n);
    vector<bool> dp(m);
    for(int i=0;i<n;i++)cin >> a[i] >> b[i];
    for(int i=1;i<m;i++){
        for(int j=0;j<n;j++)if(i>>j&1){
            for(int k=0;k<j;k++)if(i>>k&1){
                if(a[k]!=a[j]&&b[k]!=b[j])continue;
                if(!dp[i^(1<<j)^(1<<k)])dp[i]=true;
            }
        }
    }
    cout << (dp.back()?"Takahashi":"Aoki");
}
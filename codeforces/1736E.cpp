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

template<class T,class U>
bool chmax(T &a,const U &b){
    return a<b?a=T(b),true:false;
}

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<int>> dp(n,vector<int>(n+1,-INF));
    dp[0][0]=dp[0][1]=a[0];
    dp[1][0]=a[1];
    for(int i=1;i<n;i++){
        vector<vector<int>> ndp(n,vector<int>(n+1,-INF));
        vector<int> aux(n+1,-INF);
        for(int j=0;j<n;j++){
            for(int k=0;k<=n;k++){
                if(k+1<=n){
                    if(j>i){
                        chmax(ndp[j][k+1],dp[j][k]);
                    }
                    if(j<i){
                        chmax(ndp[i][k+1],dp[j][k]+a[i]);
                    }
                }
                chmax(ndp[j][k],dp[j][k]+a[j]);
            }
            for(int k=0;k<=n;k++){
                chmax(aux[k],dp[j][k]);
            }
            if(j>i){
                for(int k=0;k+j-i-1<=n;k++){
                    chmax(ndp[j][k],aux[k+j-i-1]+a[j]);
                }
            }
        }
        for(int j=0;j<n;j++){
            for(int k=n;k>=1;k--){
                chmax(ndp[j][k-1],ndp[j][k]);
            }
        }
        swap(dp,ndp);
    }
    int ans=0;
    for(auto &v:dp){
        for(auto &x:v){
            chmax(ans,x);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
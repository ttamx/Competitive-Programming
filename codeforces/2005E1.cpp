#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
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
    int l,n,m;
    cin >> l >> n >> m;
    vector<int> a(l);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> b(n,vector<int>(m));
    for(auto &v:b){
        for(auto &x:v){
            cin >> x;
        }
        reverse(v.begin(),v.end());
    }
    reverse(b.begin(),b.end());
    vector dp(n,vector<int>(m));
    for(int t=l-1;t>=0;t--){
        vector ndp(n,vector<int>(m));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(b[i][j]==a[t]&&(i==0||j==0||dp[i-1][j-1]==0)){
                    ndp[i][j]=1;
                }
                if(i>0&&ndp[i-1][j]){
                    ndp[i][j]=1;
                }
                if(j>0&&ndp[i][j-1]){
                    ndp[i][j]=1;
                }
            }
        }
        swap(dp,ndp);
    }
    cout << "NT"[dp[n-1][m-1]] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
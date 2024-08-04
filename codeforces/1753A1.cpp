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
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<bool>> dp(5,vector<bool>(2));
    dp[2][0]=true;
    for(int i=0;i<n;i++){
        vector<vector<bool>> ndp(5,vector<bool>(2));
        for(int j=0;j<5;j++){
            for(int k=0;k<2;k++){
                if(!dp[j][k])continue;
                int x=j+(k?-a[i]:a[i]);
                if(0<=x&&x<=4)ndp[x][k^1]=true;
                x=j+a[i];
                if(0<=x&&x<=4)ndp[x][1]=true;
            }
        }
        swap(dp,ndp);
    }
    cout << ((dp[2][0]||dp[2][1])?"1":"-1") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
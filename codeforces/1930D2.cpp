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
    string s;
    cin >> s;
    vl dp(n+2);
    for(int r=1;r<=min(n,3);r++){
        for(int l=1;l<=r;l++){
            for(int i=l-1;i<r;i++)if(s[i]=='1'){
                dp[r]++;
                if(s[i+2]=='1')i+=2;
                else if(s[i+1]=='1')i++;
            }
        }
    }
    for(int i=4;i<=n;i++){
        dp[i]=LINF;
        ll add=0,sum=0;
        for(int j=1;j<=3;j++){
            if(s[i-j]=='1')add=1;
            sum+=add;
            dp[i]=min(dp[i],dp[i-j]+sum+add*(i-j));
        }
    }
    cout << accumulate(1+all(dp)-1,0LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    int n,x;
    cin >> n >> x;
    x<<=1;
    x|=1;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x<<=1;
    }
    for(int i=1;i<n;i++)a[i]^=a[i-1];
    int ans=-1;
    for(int i=30;i>=0;i--){
        int s=x>>i;
        if((s&1)==0)continue;
        s^=1;
        s=~s;
        map<int,int> dp;
        dp[0]=0;
        for(int j=0;j<n;j++){
            int t=(a[j]>>i)&s;
            if(dp.count(t)){
                int val=dp[t]+1;
                if(j==n-1){
                    ans=max(ans,val);
                }
                if(dp.count(t)){
                    dp[t]=max(dp[t],val);
                }else{
                    dp[t]=val;
                }
            }
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
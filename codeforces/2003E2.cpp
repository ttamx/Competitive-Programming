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

void chmax(int &a,int b){
    if(b>a){
        a=b;
    }
}

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> a(m);
    for(auto &[l,r]:a){
        cin >> l >> r;
        l--,r--;
    }
    sort(a.begin(),a.end());
    vector<int> t(n);
    for(int i=0;i<m;){
        int first=a[i].second;
        int last=a[i].second;
        int j=i+1;
        while(j<m&&a[j].first<=last){
            last=max(last,a[j].second);
            first=min(first,a[j].second);
            j++;
        }
        for(int k=i;k<j;k++){
            if(a[k].first>=first){
                cout << -1 << "\n";
                return;
            }
        }
        for(int k=a[i].first;k<=last;k++){
            if(k<=a[j-1].first){
                t[k]=1;
            }else if(k>=first){
                t[k]=2;
            }else{
                t[k]=3;
            }
        }
        i=j;
    }
    vector<array<int,2>> dp(n+1,{-INF,-INF});
    dp[0][0]=0;
    for(int i=0;i<n;i++){
        vector<array<int,2>> ndp(n+1,{-INF,-INF});
        for(int j=0;j<=i;j++){
            if(t[i]==0){
                chmax(ndp[j+1][0],max(dp[j][0],dp[j][1])+i);
                chmax(ndp[j][1],max(dp[j][0],dp[j][1])+i-j);
            }else if(t[i]==1){
                chmax(ndp[j+1][0],max(dp[j][0],dp[j][1])+i);
            }else if(t[i]==2){
                chmax(ndp[j][1],max(dp[j][0],dp[j][1])+i-j);
            }else if(t[i]==3){
                chmax(ndp[j+1][0],dp[j][0]+i);
                chmax(ndp[j][1],max(dp[j][0],dp[j][1])+i-j);
            }else{
                assert(false);
            }
        }
        swap(dp,ndp);
    }
    int ans=0;
    for(auto x:dp){
        ans=max({ans,x[0],x[1]});
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--){
        runcase();
    }
}
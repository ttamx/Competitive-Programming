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
    vi a(n);
    for(auto &x:a)cin >> x,x--;
    if(*min_element(all(a))==*max_element(all(a)))return void(cout << "0\n");
    vector<vector<vi>> dp,dp2;
    dp=dp2=vector<vector<vi>>(n,vector<vi>(n,vi(k,INF)));
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            dp[i][i][j]=(a[i]!=j);
            dp2[i][i][j]=(a[i]==j);
        }
    }
    for(int s=1;s<n;s++){
        for(int l=0,r=s;r<n;l++,r++){
            pii mn(INF,-1),mn2(INF,-1);
            for(int i=0;i<k;i++){
                for(int m=l;m<r;m++){
                    dp[l][r][i]=min(dp[l][r][i],dp[l][m][i]+dp[m+1][r][i]);
                    dp2[l][r][i]=min(dp2[l][r][i],dp2[l][m][i]+dp2[m+1][r][i]);
                }
                dp[l][r][i]=min(dp[l][r][i],dp2[l][r][i]+1);
                mn2=min(mn2,pii(dp[l][r][i],i));
                if(mn2<mn)swap(mn,mn2);
            }
            for(int i=0;i<k;i++){
                if(mn.second!=i){
                    dp2[l][r][i]=min(dp2[l][r][i],mn.first);
                }else{
                    dp2[l][r][i]=min(dp2[l][r][i],mn2.first);
                }
            }
        }
    }
    cout << *min_element(all(dp[0][n-1])) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
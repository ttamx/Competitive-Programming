#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Frac{
    ll x,y;
    Frac():x(0),y(1){}
    Frac(ll _x):x(_x),y(1){}
    Frac(ll _x,ll _y):x(_x),y(_y){}
    const bool operator<(const Frac &o)const{return x*o.y<o.x*y;}
    const bool operator>(const Frac &o)const{return o<(*this);}
    const bool operator<=(const Frac &o)const{return !(*this>o);}
    const bool operator>=(const Frac &o)const{return !(*this<o);}
};

const int N=505;
const int MOD=1e9+7;

int n;
int a[N],b[N];
vector<pair<Frac,int>> va[N],vb[N];
int dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    for(int i=1;i<=n;i++){
        int sum=0;
        for(int j=i;j<=n;j++){
            sum+=a[j];
            va[i].emplace_back(Frac(sum,j-i+1),j);
        }
        sort(va[i].rbegin(),va[i].rend());
    }
    for(int i=1;i<=n;i++){
        int sum=0;
        for(int j=i;j>=1;j--){
            sum+=b[j];
            vb[i].emplace_back(Frac(sum,i-j+1),j);
        }
        sort(vb[i].rbegin(),vb[i].rend());
    }
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int id=0,sum=0;
            for(auto [val,k]:va[i]){
                for(;id<j&&vb[j][id].first>=val;id++){
                    sum+=dp[i-1][vb[j][id].second-1];
                    if(sum>=MOD)sum-=MOD;
                }
                dp[k][j]+=sum;
                if(dp[k][j]>=MOD)dp[k][j]-=MOD;
            }
        }
    }
    cout << dp[n][n] << "\n";
}
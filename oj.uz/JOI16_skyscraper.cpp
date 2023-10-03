#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=105;
const int M=1005;
const int mod=1e9+7;

struct mint{
    int x;
    mint(ll x=0ll):x(calc(x%mod)){}
    int calc(int x){
        if(x>=mod)x-=mod;
        if(x<0)x+=mod;
        return x;
    }
    mint& operator+=(const mint &rhs){return x=calc(x+rhs.x),*this;}
    mint& operator-=(const mint &rhs){return x=calc(x-rhs.x),*this;}
    mint& operator*=(const mint &rhs){return x=(1ll*x*rhs.x)%mod,*this;}
    friend mint operator+(const mint &lhs,const mint &rhs){return mint(lhs)+=rhs;};
    friend mint operator-(const mint &lhs,const mint &rhs){return mint(lhs)-=rhs;};
    friend mint operator*(const mint &lhs,const mint &rhs){return mint(lhs)*=rhs;};
    friend istream& operator>>(istream &is,mint &o){ll x;return is >> x,o=mint(x),is;}
    friend ostream& operator<<(ostream &os,mint &o){return os << o.x;}
};

int n,l;
int a[N];
mint dp[N][N][M][4];
mint ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> l;
    for(int i=1;i<=n;i++)cin >> a[i];
    if(n==1)cout << 1,exit(0);
    sort(a+1,a+n+1);
    dp[1][1][0][0]=1;
    dp[1][1][0][1]=2;
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            for(int k=0;k<=l;k++){
                for(int e=0;e<3;e++){
                    int res=k+(a[i]-a[i-1])*(2*j-e);
                    if(res>l)continue;
                    dp[i][j-1][res][e]+=dp[i-1][j][k][e]*(j-1);
                    dp[i][j][res][e]+=dp[i-1][j][k][e]*(2*j-e);
                    dp[i][j+1][res][e]+=dp[i-1][j][k][e]*(j+1-e);
                    dp[i][j][res][e+1]+=dp[i-1][j][k][e]*(2-e);
                    dp[i][j+1][res][e+1]+=dp[i-1][j][k][e]*(2-e);
                }
            }
        }
    }
    for(int i=0;i<=l;i++)ans+=dp[n][1][i][2];
    cout << ans;
}
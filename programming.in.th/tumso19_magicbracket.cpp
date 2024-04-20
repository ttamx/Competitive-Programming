#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=505;
const int mod=1e9+7;

int n;
string s;
ll dp[N][N],dp2[N][N];

int calc(int i,int j){
    char a=s[i],b=s[j];
    if(a=='?'&&b=='?')return 2;
    if(a=='('&&(b==')'||b=='?'))return 1;
    if((a=='('||a=='?')&&b==')')return 1;
    if(a=='['&&(b==']'||b=='?'))return 1;
    if((a=='['||a=='?')&&b==']')return 1;
    return 0;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> s;
    for(int i=1;i<n;i++)dp[i-1][i]=dp2[i-1][i]=calc(i-1,i);
    for(int sz=4;sz<=n;sz+=2){
        for(int l=0,r=sz-1;r<n;l++,r++){
            dp[l][r]=dp2[l][r]=dp2[l+1][r-1]*calc(l,r);
            for(int m=l+1;m<r;m+=2){
                dp2[l][r]+=dp[l][m]*dp2[m+1][r];
                dp2[l][r]%=mod;
            }
        }
    }
    cout << dp2[0][n-1];
}
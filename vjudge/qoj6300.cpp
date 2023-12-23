#include<bits/stdc++.h>

using namespace std;

using ll = __int128_t;
using vi = vector<int>;
using vl = vector<ll>;

const ll inf=ll(4e18)*ll(4e18);

string ll2s(ll x){
    if(x==0)return "0";
    string s="";
    while(x>0){
        s+=char(x%10+'0');
        x/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}

void solve(){
    string s;
    int k;
    cin >> s >> k;
    reverse(s.begin(),s.end());
    if(k==0){
        int p=0;
        string ans="";
        while(p<s.size()&&s[p]=='9')ans+='0',p++;
        cout << "1"+ans << "\n";
        return;
    }
    vector<vector<vl>> dp(40,vector<vl>(k+2,vl(2,inf)));
    dp[0][0][0]=0;
    ll pw=1;
    for(int i=1;i<=39;i++,pw*=10){
        int num=i>s.size()?0:(s[i-1]-'0');
        for(int j=0;j<=k;j++){
            for(int c=0;c<2;c++){
                int d=10-num-c;
                if(d>0)dp[i][j][0]=min(dp[i][j][0],dp[i-1][j][c]);
                if(d<10)dp[i][j+1][1]=min(dp[i][j+1][1],dp[i-1][j][c]+d*pw);
            }
        }
    }
    cout << ll2s(dp[39][k][0]) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}
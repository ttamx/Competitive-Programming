#include<bits/stdc++.h>

using namespace std;

const int N=205;

int n;
string str;

struct DP{
    int len,i,rep;
    DP():len(1e9){}
    DP(int len,int i,int rep)
        :len(len),i(i),rep(rep){}
    bool operator<(const DP &o)const{
        return len<o.len;
    }
}dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> str;
    n=str.size();
    for(int i=0;i<n;i++){
        dp[i][i]=DP(1,-1,0);
        for(int j=2;j<=9;j++){
            if(i+j-1>=n)break;
            if(str[i]!=str[i+j-1])break;
            dp[i][i+j-1]=DP(4,i,j);
        }
    }
    for(int s=2;s<=n;s++){
        for(int l=0,r=s-1;r<n;l++,r++){
            for(int i=l;i<r;i++){
                dp[l][r]=min(dp[l][r],DP(dp[l][i].len+dp[i+1][r].len,i,0));
            }
            for(int i=2;i<=9;i++){
                int nr=l+i*s-1;
                if(nr>=n)break;
                if(str.substr(l,s)!=str.substr(l+(i-1)*s,s)){
                    break;
                }
                dp[l][nr]=min(dp[l][nr],DP(dp[l][r].len+3,r,i));
            }
        }
    }
    string ans="";
    function<void(int,int)> solve=[&](int l,int r){
        if(l==r){
            ans+=str[l];
            return;
        }
        if(dp[l][r].rep){
            ans+=char('0'+dp[l][r].rep);
            ans+='(';
            solve(l,dp[l][r].i);
            ans+=')';
        }else{
            solve(l,dp[l][r].i);
            solve(dp[l][r].i+1,r);
        }
    };
    solve(0,n-1);
    cout << ans << "\n";
}
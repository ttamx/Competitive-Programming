#include<bits/stdc++.h>

using namespace std;

const int N=3005;

string a,b,s;
int dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> a >> b;
    a=" "+a;
    b=" "+b;
    for(int i=1;i<a.size();i++){
        for(int j=1;j<b.size();j++){
            dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            if(a[i]==b[j])dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
        }
    }
    int i=a.size()-1,j=b.size()-1;
    while(i>0&&j>0){
        if(a[i]==b[j]&&dp[i][j]==dp[i-1][j-1]+1){
            s=a[i]+s;
            i--,j--;
        }else if(dp[i][j]==dp[i-1][j]){
            i--;
        }else{
            j--;
        }
    }
    cout << s;
}
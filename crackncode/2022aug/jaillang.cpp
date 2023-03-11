#include<bits/stdc++.h>

using namespace std;

int r,c;
int dp[505][505];

int calc(int a,int b,int c,int d){
    --a,--b;
    return dp[c][d]-dp[a][d]-dp[c][b]+dp[a][b];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> r >> c;
    for(int i=1;i<=r;++i){
        for(int j=1;j<=c;++j){
            char s;
            cin >> s;
            dp[i][j]=(0?1:s=='O')+dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
        }
    }
    for(int sz=min((r+1)/2,c);sz>=3;--sz){
        for(int i=1;i+sz*2-2<=r;++i){
            for(int j=1;j+sz-1<=c;++j){
                if(calc(i,j,i+(sz*2)-2,j+sz-1)-calc(i+1,j+1,i+sz-2,j+sz-1)-calc(i+sz,j,i+(sz*2)-3,j+sz-2)==0){
                    cout << sz;
                    return 0;
                }
            }
        }
    }
    cout << 0;
    return 0;
}

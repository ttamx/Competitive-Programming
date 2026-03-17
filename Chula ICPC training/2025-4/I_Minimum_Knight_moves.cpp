#include<bits/stdc++.h>

using namespace std;

const int N=64;

int dp[N][N];

void add(int i1,int j1,int i2,int j2){
    if(i2<0||i2>=8||j2<0||j2>=8)return;
    dp[i1*8+j1][i2*8+j2]=dp[i2*8+j2][i1*8+j1]=1;
}

int get(){
    string s;
    cin >> s;
    return (s[0]-'a')*8+s[1]-'1';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(i!=j){
                dp[i][j]=INT_MAX/2;
            }
        }
    }
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            add(i,j,i-1,j-2);
            add(i,j,i-1,j+2);
            add(i,j,i-2,j-1);
            add(i,j,i-2,j+1);
        }
    }
    for(int x=0;x<N;x++){
        for(int u=0;u<N;u++){
            for(int v=0;v<N;v++){
                dp[u][v]=min(dp[u][v],dp[u][x]+dp[x][v]);
            }
        }
    }
    int q;
    cin >> q;
    while(q--){
        cout << dp[get()][get()] << "\n";
    }
}
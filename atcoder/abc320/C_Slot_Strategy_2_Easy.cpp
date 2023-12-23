#include<bits/stdc++.h>

using namespace std;

const int M=105;

int m;
string s[4];
int dp[10][M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m;
    for(int i=0;i<3;i++){
        cin >> s[i];
        s[i]=s[i]+s[i]+s[i];
    }
    
}
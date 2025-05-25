#include<bits/stdc++.h>

using namespace std;

const int N=260;

int n;
int a[N];
bool dp[N][N][3];
int table[3][3];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    table[0][0]=2;
    table[0][1]=1;
    table[0][2]=0;
    table[1][0]=2;
    table[1][1]=1;
    table[1][2]=1;
    table[2][0]=1;
    table[2][1]=2;
    table[2][2]=1;
    for(int t=0;t<20;t++){
        cin >> n;
        string s;
        cin >> s;
        for(int i=1;i<=n;i++){
            a[i]=s[i-1]-'0';
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                for(int v=0;v<3;v++){
                    dp[i][j][v]=false;
                }
            }
        }
        for(int i=1;i<=n;i++){
            dp[i][i][a[i]]=true;
        }
        for(int sz=2;sz<=n;sz++){
            for(int l=1,r=sz;r<=n;l++,r++){
                for(int m=l;m+1<=r;m++){
                    for(int vl=0;vl<3;vl++){
                        if(!dp[l][m][vl])continue;
                        for(int vr=0;vr<3;vr++){
                            if(!dp[m+1][r][vr])continue;
                            int v=table[vl][vr];
                            dp[l][r][v]=true;
                        }
                    }
                }
            }
        }
        cout << (dp[1][n][0]?"yes":"no") << "\n";
    }
}
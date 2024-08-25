#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int INF=INT_MAX/2;

int n;
int dp[2][4][4][4][4];
string s;
int ans;

int calc(int a,int b,int c){
    if(a==0)return (b==0||b==c)?1:2;
    if(a==b&&a==c)return 1;
    if(a==b||a==c||b==c)return 2;
    return 3;
}

void chmax(int &x,int v){
    if(v>x)x=v;
}
void clear(int i){
    for(int x=0;x<4;x++){
        for(int y=0;y<4;y++){
            for(int z=0;z<4;z++){
                for(int w=0;w<4;w++){
                    dp[i&1][x][y][z][w]=-INF;
                }
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    cin >> s;
    clear(0);
    dp[0][0][0][0][0]=0;
    for(int i=0;i<n;i++){
        clear(i+1);
        int v=s[i]=='M'?1:s[i]=='F'?2:3;
        for(int x=0;x<4;x++){
            for(int y=0;y<4;y++){
                for(int z=0;z<4;z++){
                    for(int w=0;w<4;w++){
                        chmax(dp[i&1^1][x][y][w][v],dp[i&1][x][y][z][w]+calc(z,w,v));
                        chmax(dp[i&1^1][y][v][z][w],dp[i&1][x][y][z][w]+calc(x,y,v));
                    }
                }
            }
        }
    }
    for(int x=0;x<4;x++){
        for(int y=0;y<4;y++){
            for(int z=0;z<4;z++){
                for(int w=0;w<4;w++){
                    chmax(ans,dp[n&1][x][y][z][w]);
                }
            }
        }
    }
    cout << ans;
}
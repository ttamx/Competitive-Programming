#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int Q=5e5+5;
const int M=505;
const int T=55;

int n,q;
int a[T][M][M];
int ans[T];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int x,y;
        cin >> x >> y;
        x+=250,y+=250;
        a[0][x][y]=1;
        ans[0]++;
    }
    for(int t=0;t<T-1;t++){
        for(int i=1;i<M-1;i++){
            for(int j=1;j<M-1;j++){
                if(a[t][i][j]==0){
                    if(a[t][i-1][j]==1||a[t][i+1][j]==1||a[t][i][j-1]==1||a[t][i][j+1]==1){
                        a[t+1][i][j]=1;
                        ans[t+1]++;
                    }else{
                        a[t+1][i][j]=0;
                    }
                }else{
                    a[t+1][i][j]=(a[t][i][j]+1)%3;
                }
            }
        }
    }
    while(q--){
        int t;
        cin >> t;
        cout << ans[t] << "\n";
    }
}
#include<bits/stdc++.h>

using namespace std;

const int K=605;
const int M=1505;
const int mod=1e6+3;

int r,c,k,ans;
int a[2][M][M];
int C[K][K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> r >> c >> k;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            char x;
            cin >> x;
            a[0][i+600][j+600]=a[1][i+600][j+600]=(x=='#');
        }
    }
    for(int i=1;i<M-1;i++)for(int j=1;j<M-1;j++)a[0][i][j]+=a[0][i-1][j-1],a[1][i][j]+=a[1][i-1][j+1];
    for(int i=0;i<K;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
    }
    for(int s=1;s<=r+c;s++){
        for(int i=601;i<=r+600;i++){
            for(int j=601;j<=c+600;j++){
                int cnt=0;
                cnt+=a[0][i-1][j+s-1]-a[0][i-s-1][j-1];
                cnt+=a[0][i+s][j]-a[0][i][j-s];
                cnt+=a[1][i+s-1][j+1]-a[1][i-1][j+s+1];
                cnt+=a[1][i][j-s]-a[1][i-s][j];
                ans+=C[cnt][k];
                ans%=mod;
            }
        }
    }
    cout << ans;
}
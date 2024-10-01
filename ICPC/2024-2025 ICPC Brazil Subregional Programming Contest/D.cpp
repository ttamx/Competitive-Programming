#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int K=128;
const int N=1e5+5;
const int MOD=1e9+7;

int n;
ll m;
ll g1[K][K],g2[K][K],dp[K][K];
vector<int> a[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m;
    cin >> n;
    for(int i=0;i<n;i++){
        int x,y;
        cin >> x >> y;
        a[y].emplace_back(x);
    }
    for(int i=0;i<K;i++)g1[i][i]=1;
    for(int i=0;i<7;i++){
        int b=1<<i;
        for(int j=0;j<K;j+=b){
            for(auto x:a[i]){
                int k=j-x;
                if(k<0){
                    g2[j][k+b]++;
                }else{
                    g1[j][k]++;
                }
            }
        }
    }
    for(int i=0;i<K;i++){
        for(int j=i+2;j<K;j++){
            for(int k=i+1;k<j;k++){
                g1[i][j]+=g1[i][k]*g1[k][j];
                g1[i][j]%=MOD;
            }
        }
    }
    for(int i=0;i<K;i++){
        for(int j=0;j<K;j++){
            for(int x=0;x<=i;x++){
                for(int y=j;y<K;y++){
                    dp[i][j]+=g1[i][x]*g2[x][y]%MOD*g1[y][j]%MOD;
                    dp[i][j]%=MOD;
                }
            }
        }
    }
}
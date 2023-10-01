#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=205;
const ll mod=1e9+7;
const int P=30;

int n,m,q;

struct mat:array<array<ll,N>,N>{
    mat(ll x=0){
        for(int i=0;i<N;i++)for(int j=0;j<N;j++)(*this)[i][j]=x;
    }
    friend mat operator*(mat a,mat b){
        mat c;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                for(int k=0;k<N;k++){
                    c[i][j]+=a[i][k]*b[k][j];
                    c[i][j]%=mod;
                }
            }
        }
        return c;
    }
}dp[P];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        dp[0][u][v]++;
    }
    for(int i=1;i<P;i++)dp[i]=dp[i-1]*dp[i-1];
    while(q--){
        int u,v,k;
        cin >> u >> v >> k;
        vector<ll> res(N);
        res[u]=1;
        for(int i=0;i<P;i++){
            if(!(k>>i&1))continue;
            vector<ll> tmp(N);
            for(int j=0;j<N;j++){
                for(int k=0;k<N;k++){
                    tmp[k]+=res[j]*dp[i][j][k];
                    tmp[k]%=mod;
                }
            }
            res=tmp;
        }
        cout << res[v] << "\n";
    }
}
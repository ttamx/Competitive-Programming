#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int N=105;

int n,m;
string s;
int fail[N];
int nxt[N][2];

struct Matrix:array<array<mint,N>,N>{
    Matrix(){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                this->at(i).at(j)=0;
            }
        }
    }
    friend Matrix operator*(const Matrix &l,const Matrix &r){
        Matrix res;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                for(int k=0;k<N;k++){
                    res[i][j]+=l[i][k]*r[k][j];
                }
            }
        }
        return res;
    }
}dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    cin >> s;
    for(int i=0;i<n;i++){
        int p=fail[i];
        int x=s[i]-'0';
        nxt[i][x]=i+1;
        nxt[i][x^1]=nxt[p][x^1];
        if(i)fail[i+1]=nxt[p][x];
    }
    nxt[n][0]=nxt[fail[n]][0];
    nxt[n][1]=nxt[fail[n]][1];
    for(int t=0;t<2;t++){
        for(int i=0;i<=n;i++)dp[t][i][i]=1;
        dp[t][n+1][n+1]=2;
        for(int i=0;i<=n;i++){
            int j=nxt[i][t];
            dp[t][i][j]++;
            if(j==n)dp[t][i][n+1]++;
        }
    }
    for(int i=2;i<=m;i++){
        dp[i]=dp[i-1]*dp[i-2];
    }
    cout << dp[m][0][n+1] << "\n";
}
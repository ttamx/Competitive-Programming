#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=50;
const ll INF=1e18;

struct Matrix:array<array<ll,N>,N>{
    Matrix(){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                this->at(i).at(j)=INF;
            }
        }
    }
    static Matrix identity(){
        static Matrix res;
        for(int i=0;i<N;i++)res[i][i]=0;
        return res;
    }
    friend Matrix operator*(const Matrix &l,const Matrix &r){
        Matrix res;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                for(int k=0;k<N;k++){
                    res[i][j]=min(res[i][j],l[i][k]+r[k][j]);
                }
            }
        }
        return res;
    }    
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    Matrix base;
    for(int st=0;st<N;st++){
        vector<ll> dp(N,INF);
        dp[st]=0;
        for(int i=0;i<n;i++){
            vector<ll> ndp(N,INF);
            for(int j=0;j<N;j++){
                if(j+1<N)ndp[j+1]=min(ndp[j+1],dp[j]+a[i]);
                if(j>0)ndp[j-1]=min(ndp[j-1],dp[j]+b[i]);
            }
            dp=move(ndp);
        }
        for(int i=0;i<N;i++)base[st][i]=dp[i];
    }
    Matrix res=Matrix::identity();
    while(m>0){
        if(m&1)res=res*base;
        base=base*base;
        m>>=1;
    }
    cout << res[0][0] << "\n";
}
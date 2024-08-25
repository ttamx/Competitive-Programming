#include<bits/stdc++.h>

using namespace std;

const int S=10;
const int INF=INT_MAX/2;

struct Matrix:array<array<int,S>,S>{
    Matrix(){
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                (*this)[i][j]=0;
            }
        }
    }
    Matrix(int v){
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                (*this)[i][j]=v;
            }
        }
    }
    static Matrix identity(){
        Matrix res(INF);
        for(int i=0;i<S;i++){
            res[i][i]=0;
        }
    }
    friend Matrix operator*(const Matrix &a,const Matrix &b){
        Matrix c(INF);
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                for(int k=0;k<S;k++){
                    c[i][j]=min(c[i][j],a[i][k]+b[k][j]);
                }
            }
        }
        return c;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    auto get_matrix=[&](int x){
        int v=s[x]-'0';
        Matrix res(INF);
        for(int i=0;i<9;i++){
            res[i][i]=0;
        }
        res[9][v-1]=-v*x;
        for(int i=0;i<9;i++){
            res[i][9]=(i+1)*x;
        }
        return res;
    };
    vector<Matrix> dpl(n),dpr(n);
    for(int l=0,r=k-1;l<n;l+=k,r+=k){
        r=min(r,n-1);
        dpl[l]=get_matrix(l);
        for(int i=l+1;i<=r;i++){
            dpl[i]=dpl[i-1]*get_matrix(i);
        }
        dpr[r]=get_matrix(r);
        for(int i=r-1;i>=l;i--){
            dpr[i]=get_matrix(i)*dpr[i+1];
        }
    }
    for(int l=0,r=k-1;r<n;l++,r++){
        Matrix cur=(l%k==0?dpl[r]:dpr[l]*dpl[r]);
        cout << cur[9][9] << " ";
    }
}
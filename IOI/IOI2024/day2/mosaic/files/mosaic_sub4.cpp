#include <bits/stdc++.h>

using namespace std;

using ll = long long;

vector<ll> mosaic(vector<int> X,vector<int> Y,vector<int> T,vector<int> B,vector<int> L,vector<int> R){
    int n=X.size();
    int q=T.size();
    vector<ll> ans(q);
    vector<vector<int>> a(n,vector<int>(n));
    a[0]=X;
    for(int i=1;i<n;i++)a[i][0]=Y[i];
    for(int i=1;i<n;i++){
        for(int j=1;j<n;j++){
            if(a[i-1][j]+a[i][j-1]==0){
                a[i][j]=1;
            }
        }
    }
    for(auto v:a){
        for(auto x:v){
            cerr << x << " ";
        }
        cerr << "\n";
    }
    auto b=a;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i>0){
                b[i][j]+=b[i-1][j];
            }
            if(j>0){
                b[i][j]+=b[i][j-1];
            }
            if(i>0&&j>0){
                b[i][j]-=b[i-1][j-1];
            }
        }
    }
    for(int i=0;i<q;i++){
        ans[i]=b[B[i]][R[i]];
        if(T[i]>0){
            ans[i]-=b[T[i]-1][R[i]];
        }
        if(L[i]>0){
            ans[i]-=b[B[i]][L[i]-1];
        }
        if(T[i]>0&&L[i]>0){
            ans[i]+=b[T[i]-1][L[i]-1];
        }
    }
    return ans;
}

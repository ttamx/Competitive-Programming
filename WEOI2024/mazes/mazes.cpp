#include <bits/stdc++.h>

using namespace std;

vector<vector<char>> solve(long long k){
    int n=119,m=121;
    vector<vector<char>> a(n,vector<char>(m,'.'));
    for(int i=1;i<n;i+=2)a[i][i]='#';
    for(int i=1;i<n;i+=2)for(int j=1;j<m;j+=2)a[i][j]='#';
    for(int i=1;i<n;i+=2)for(int j=i+2;j<m-1;j++)a[i][j]='#';
    for(int i=1;i<n;i+=2)for(int j=0;j<=i-2;j++)a[i][j]='#';
    for(int i=0;i*2<n;i++)if(!(k>>i&1))a[i*2][m-2]='#';
    return a;
}
#include<bits/stdc++.h>

using namespace std;

long long mod=1e9+7;

struct matrix{
    long long m[4][4]={};
    friend matrix operator*(matrix a,matrix b){
        matrix c;
        for(int i=0;i<4;i++)for(int j=0;j<4;j++)for(int k=0;k<4;k++)c.m[i][j]+=a.m[i][k]*b.m[k][j]%mod,c.m[i][j]%=mod;
        return c;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    matrix a;
    a.m[0][1]=1;
    a.m[1][2]=1;
    a.m[1][3]=1;
    a.m[2][0]=1;
    a.m[2][1]=1;
    a.m[3][2]=1;
    long long n;
    cin >> n;
    if(n<3){
        cout << 0;
        return 0;
    }
    matrix ans;
    ans.m[0][0]=1;
    ans.m[1][1]=1;
    ans.m[2][2]=1;
    ans.m[3][3]=1;
    while(n){
        if(n&1)ans=ans*a;
        a=a*a;
        n/=2;
    }
    cout << ans.m[0][0];
}
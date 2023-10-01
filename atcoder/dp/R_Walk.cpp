#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=55;
const int mod=1e9+7;

int n;
ll k;
ll ans=0;

struct mat:array<array<ll,N>,N>{
    mat(){
        for(int i=0;i<N;i++)for(int j=0;j<N;j++)(*this)[i][j]=0;
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
}a,g;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin >> a[i][j];
    for(int i=0;i<n;i++)g[i][i]=1;
    while(k>0){
        if(k&1)g=g*a;
        a=a*a;
        k>>=1;
    }
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)ans+=g[i][j],ans%=mod;
    cout << ans;
}
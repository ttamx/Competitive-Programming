#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int S=3;
const ll INF=LLONG_MAX/2;

int n;
ll m;

struct Mat:array<array<ll,S>,S>{
    Mat(){for(int i=0;i<S;i++)for(int j=0;j<S;j++)this->at(i).at(j)=INF;}
    static Mat iden(){
        static Mat res;
        for(int i=0;i<S;i++)res[i][i]=0LL;
        return res;
    }
    friend Mat operator*(Mat l,Mat r){
        Mat res;
        for(int i=0;i<S;i++)for(int j=0;j<S;j++)for(int k=0;k<S;k++)res[i][j]=min(res[i][j],l[i][k]+r[k][j]);
        return res;
    }
}f[4],dp[60];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    map<ll,ll> a;
    for(int i=0;i<n;i++){
        ll x,y;
        cin >> x >> y;
        a[y]|=x;
    }
    f[0][0][0]=0;
    f[0][1][2]=0;
    f[0][2][1]=0;
    f[1][0][1]=1;
    f[1][0][2]=0;
    f[1][1][0]=1;
    f[1][2][0]=0;
    f[2][0][2]=1;
    f[2][0][1]=0;
    f[2][2][0]=1;
    f[2][1][0]=0;
    f[3][0][0]=0;
    f[3][1][1]=1;
    f[3][1][2]=2;
    f[3][2][2]=1;
    f[3][2][1]=2;
    for(int i=)
}
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int M=52;
const int MOD=1e9+7;

struct Mat:array<array<ll,M>,M>{
    Mat(){
        for(int i=0;i<M;i++){
            for(int j=0;j<M;j++){
                this->at(i).at(j)=0LL;
            }
        }
    }
    friend Mat operator*(const Mat &l,const Mat &r){
        Mat res;
        for(int i=0;i<M;i++){
            for(int j=0;j<M;j++){
                for(int k=0;k<M;k++){
                    res[i][j]=(res[i][j]+l[i][k]*r[k][j])%MOD;
                }
            }
        }
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n,m,k;
    cin >> n >> m >> k;
    Mat base;
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            base[i][j]=1;
        }
    }
    for(int i=0;i<k;i++){
        char u,v;
        cin >> u >> v;
        u=u>='a'?u-'a':u-'A'+26;
        v=v>='a'?v-'a':v-'A'+26;
        base[u][v]=0;
    }
    Mat mat;
    for(int i=0;i<m;i++){
        mat[i][i]=1;
    }
    n--;
    while(n>0){
        if(n&1)mat=mat*base;
        base=base*base;
        n>>=1;
    }
    ll ans=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            ans=(ans+mat[i][j])%MOD;
        }
    }
    cout << ans << "\n";
}
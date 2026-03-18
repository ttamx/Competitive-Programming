#include<bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;

using ll = long long;

const int N=7;
const int S=128;

using V = array<ll,S>;

struct Matrix:array<V,S>{
    Matrix(){
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                this->at(i).at(j)=0;
            }
        }
    }
    friend Matrix operator*(const Matrix &l,const Matrix &r){
        Matrix res;
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                for(int k=0;k<S;k++){
                    res[i][j]+=l[i][k]*r[j][k]%MOD;
                }
                res[i][j]%=MOD;
            }
        }
        return res;
    }
    friend V operator*(const V &l,const Matrix &r){
        V res{};
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                res[i]+=l[j]*r[j][i]%MOD;
            }
            res[i]%=MOD;
        }
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    V cur{};
    cur[0]=1;
    int st=-1,ed=-1,last=0;
    ll ans=1;
    for(int s=1;s<=7;s++){
        int n;
        cin >> n;
        if(n==0)continue;
        int mask=0;
        for(;last<s;last++){
            mask|=1<<last;
        }
        for(int i=0;i<S;i++){
            if(!(i&mask)){
                cur[i|mask]=cur[i];
                cur[i]=0;
            }
        }
        Matrix mat;
        for(int i=0;i<(1<<s);i++){
            for(int j=0;j<(1<<s);j++){
                array<ll,2> dp{};
                dp[1]=1;
                for(int t=0;t<s;t++){
                    if((i>>t&1)&&(j>>t&1)){
                        tie(dp[0],dp[1])=make_pair(dp[0]+dp[1],dp[0]);
                    }else{
                        dp[0]=dp[1]=dp[0]+dp[1];
                    }
                }
                mat[i][j]=dp[1];
            }
        }
        while(n>0){
            if(n&1)cur=cur*mat;
            mat=mat*mat;
            n>>=1;
        }
        ans=cur[(1<<s)-1];
    }
    cout << ans << "\n";
}
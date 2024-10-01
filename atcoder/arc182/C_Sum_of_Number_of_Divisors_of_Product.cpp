#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

const int B=6;
const int S=1<<B;

struct Matrix:array<array<mint,S+1>,S+1>{
    Matrix(){
        for(int i=0;i<=S;i++){
            for(int j=0;j<=S;j++){
                (*this)[i][j]=0;
            }
        }
    }
    static Matrix Identity(){
        Matrix res;
        for(int i=0;i<=S;i++){
            res[i][i]=1;
        }
        return res;
    }
    friend Matrix operator*(const Matrix &a,const Matrix &b){
        Matrix res;
        for(int i=0;i<=S;i++){
            for(int j=0;j<=S;j++){
                for(int k=0;k<=S;k++){
                    res[i][j]+=a[i][k]*b[k][j];
                }
            }
        }
        return res;
    }
    friend Matrix operator+(const Matrix &a,const Matrix &b){
        Matrix res;
        for(int i=0;i<=S;i++){
            for(int j=0;j<=S;j++){
                res[i][j]=a[i][j]+b[i][j];
            }
        }
        return res;
    }
};

struct Info{
    array<mint,S> sum;
    Info(){
        for(int i=0;i<S;i++)sum[i]=0;
        sum[0]=1;
    }
    Info(array<mint,6> a){
        for(int i=0;i<S;i++){
            sum[i]=1;
            for(int j=0;j<B;j++){
                if(i>>j&1){
                    sum[i]*=a[j];
                }
            }
        }
    }
    Info add(int x,mint v){
        Info res;
        for(int i=0;i<S;i++){
            res.sum[i]=sum[i];
            if(i>>x&1){
                res.sum[i]+=v*sum[i^(1<<x)];
            }
        }
        return res;
    }
    friend Info operator+(const Info &a,const Info &b){
        Info res;
        for(int i=0;i<S;i++){
            res.sum[i]=a.sum[i]+b.sum[i];
        }
        return res;
    }
};

Matrix construct(int x,mint v){
    Matrix res;
    for(int i=0;i<S;i++){
        res[i][i]=1;
        if(i>>x&1){
            res[i^(1<<x)][i]=v;
        }
    }
    return res;
}

void runcase(){
    ll n;
    int m;
    cin >> n >> m;
    vector<int> prime{2,3,5,7,11,13};
    // mint ans=0;
    // Info dp({1,1,1,1,1,1});
    // for(int i=1;i<=n;i++){
    //     Info ndp=dp;
    //     for(int j=2;j<=m;j++){
    //         int x=j;
    //         Info tmp=dp;
    //         for(int k=0;k<B;k++){
    //             int cnt=0;
    //             while(x%prime[k]==0){
    //                 x/=prime[k];
    //                 cnt++;
    //             }
    //             if(cnt){
    //                 tmp=tmp.add(k,mint(cnt));
    //             }
    //         }
    //         ndp=ndp+tmp;
    //     }
    //     dp=ndp;
    //     ans+=dp.sum[S-1];
    // }
    Matrix base;
    for(int i=1;i<=m;i++){
        int x=i;
        Matrix tmp=Matrix::Identity();
        for(int j=0;j<B;j++){
            int cnt=0;
            while(x%prime[j]==0){
                x/=prime[j];
                cnt++;
            }
            if(cnt){
                tmp=tmp*construct(j,mint(cnt));
            }
        }
        base=base+tmp;
    }
    for(int i=0;i<S;i++){
        base[i][S]=base[i][S-1];
    }
    base[S][S]=1;
    Matrix res=Matrix::Identity();
    while(n){
        if(n&1){
            res=res*base;
        }
        base=base*base;
        n>>=1;
    }
    mint ans=0;
    for(int i=0;i<S;i++){
        ans+=res[i][S];
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
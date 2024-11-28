#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int M=10;
const int S=31;
const int B=60;
const int MOD=3359232;

ll single[M][M];
int id[4][4][4];

ll dp[10][4][4][4];

struct Matrix:array<array<int,S>,S>{
    Matrix(){
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                (*this)[i][j]=0;
            }
        }
    }
    friend Matrix operator*(const Matrix &lhs,const Matrix &rhs){
        Matrix res;
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                for(int k=0;k<S;k++){
                    res[i][j]=(res[i][j]+1LL*lhs[i][k]*rhs[k][j])%MOD;
                }
            }
        }
        return res;
    }

}base,pw[B];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int node_id=0;
    for(int x=0;x<1;x++){
        for(int y=x;y<4;y++){
            for(int z=y;z<4;z++){
                id[x][y][z]=node_id++;
            }
        }
    }
    for(int i=0;i<20;i++){
        base[i+10][i]=1;
    }
    base[0][20]=MOD-1;
    for(int i=0;i<3;i++){
        for(int x=0;x<1;x++){
            for(int y=x;y<4;y++){
                for(int z=y;z<4;z++){
                    ll mul=1;
                    if(x+y+z==0){
                        mul=2;
                    }
                    for(auto p:{1,3}){
                        vector<int> a{x+p,y,z};
                        sort(a.begin(),a.end());
                        int d=a[0];
                        if(i==0&&d==0){
                            single[id[x][y][z]][id[a[0]][a[1]][a[2]]]+=mul;
                        }else if(i+d==3){
                            base[id[x][y][z]+i*10][id[a[0]-d][a[1]-d][a[2]]-d+20]+=mul;
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<30;j++){
            for(int k=0;k<i;k++){
                base[j][i+20]+=base[j][k+20]*single[k][i];
            }
        }
    }
    base[10][30]=1;
    base[30][30]=1;
    swap(base,pw[0]);
    for(int i=1;i<B;i++){
        pw[i]=pw[i-1]*pw[i-1];
    }
    dp[0][0][0][0]=1;
    for(int i=0;i<3;i++){
        for(int x=0;x<1;x++){
            for(int y=x;y<4;y++){
                for(int z=y;z<4;z++){
                    ll cur=dp[i][x][y][z];
                    base[0][id[x][y][z]+i*10]=cur;
                    if(x+y+z==0){
                        cur*=2;
                    }
                    for(auto p:{1,3}){
                        vector<int> a{x+p,y,z};
                        sort(a.begin(),a.end());
                        int d=a[0];
                        auto &v=dp[i+d][a[0]-d][a[1]-d][a[2]-d];
                        v+=cur;
                    }
                }
            }
        }
    }
    int q;
    cin >> q;
    while(q--){
        ll n;
        cin >> n;
        n/=3;
        auto ans=base;
        for(int i=0;i<B;i++){
            if(n>>i&1){
                ans=ans*pw[i];
            }
        }
        cout << ans[0][30] << "\n";
    }
}
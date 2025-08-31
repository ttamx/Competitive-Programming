#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=1<<19;
const int S=6;
const int INF=INT_MAX/2;

struct Matrix:array<array<int,S>,S>{
    Matrix(){
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                this->at(i).at(j)=INF;
            }
        }
    }
    friend Matrix operator*(const Matrix &l,const Matrix &r){
        Matrix res;
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                for(int k=0;k<S;k++){
                    res[i][j]=min(res[i][j],l[i][k]+r[k][j]);
                }
            }
        }
        return res;
    }
};

Matrix make(int num){
    Matrix res;
    for(int i=0;i<S;i++){
        res[i][i]=0;
    }
    if(num==2){
        res[0][0]=1;
        res[0][1]=0;
    }else if(num==0){
        res[1][1]=1;
        res[1][2]=0;
    }else if(num==1){
        res[2][2]=1;
        res[2][3]=0;
    }else if(num==7){
        res[3][3]=1;
        res[3][4]=0;
    }else if(num==6){
        res[3][3]=1;
        res[4][4]=1;
        res[3][5]=0;
        res[4][5]=0;
    }
    return res;
}

int n,q;
string s;

struct Segtree{
    Matrix t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=make(s[l-1]-'0'));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]*t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    Matrix query(int l,int r,int i,int x,int y){
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        if(y<=m)return query(l,m,i*2,x,y);
        if(x>m)return query(m+1,r,i*2+1,x,y);
        return query(l,m,i*2,x,y)*query(m+1,r,i*2+1,x,y);
    }
    Matrix query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    cin >> s;
    seg.build();
    while(q--){
        int l,r;
        cin >> l >> r;
        int res=seg.query(l,r)[0][4];
        cout << (res<INF?res:-1) << "\n";
    }
}
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const int K=1<<19;
const int S=2;
const ll mod=1e9+7;

int n,q;
string str;

struct mat:array<array<ll,S>,S>{
    mat(ll x=0){
        for(int i=0;i<S;i++)for(int j=0;j<S;j++)(*this)[i][j]=x;
    }
    friend mat operator*(mat a,mat b){
        mat c;
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                for(int k=0;k<S;k++){
                    c[i][j]+=a[i][k]*b[k][j];
                    c[i][j]%=mod;
                }
            }
        }
        return c;
    }
}sad,hap,vow,def,all;

mat getmat(char c){
    switch(c){
        case 'S':return sad;
        case 'D':return sad;
        case 'H':return hap;
        case 'A':return vow;
        case 'E':return vow;
        case 'I':return vow;
        case 'O':return vow;
        case 'U':return vow;
        case '?':return all;
    }
    return def;
}

struct segtree{
    mat t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=getmat(str[l]));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]*t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int &x,mat &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]*t[i*2+1];
    }
    void update(int x,mat v){
        update(1,n,1,x,v);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    sad[0][1]=sad[1][1]=1;
    hap[0][0]=hap[1][0]=1;
    vow[0][1]=vow[1][0]=1;
    def[0][0]=def[1][1]=1;
    all[0][0]=19,all[0][1]=7,all[1][0]=6,all[1][1]=20;
    cin >> n >> q >> str;
    str=" "+str;
    s.build();
    cout << s.t[1][0][0] << "\n";
    while(q--){
        int x;
        char c;
        cin >> x >> c;
        s.update(x,getmat(c));
        cout << s.t[1][0][0] << "\n";
    }
}
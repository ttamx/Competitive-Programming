#include<bits/stdc++.h>

using namespace std;

template<class T>
T binpow(T num,long long pow){
    T res=1;
    for(;pow;num*=num,pow>>=1)if(pow&1)res*=num;
    return res;
}

const long long mod=1e9+7;

struct modular{
    long long val;
    long long norm(long long x){if(x>=mod)x-=mod; if(x<0)x+=mod; return x;}
    modular(long long x=0):val(norm(x%mod)){}
    modular inv()const{return binpow(*this,mod-2);}
    modular& operator+=(const modular&o){val=norm(val+o.val); return *this;}
    modular& operator-=(const modular&o){val=norm(val-o.val); return *this;}
    modular& operator*=(const modular&o){val=(val*o.val)%mod; return *this;}
    modular& operator/=(const modular&o){val=(val*o.inv().val)%mod; return *this;}
    modular& operator++(){return *this+=1;}
    modular& operator--(){return *this-=1;}
    modular operator++(int){modular ret=*this; *this+=1; return ret;}
    modular operator--(int){modular ret=*this; *this-=1; return ret;}
    friend modular operator+(const modular &lhs,const modular &rhs){return modular(lhs)+=rhs;}
    friend modular operator-(const modular &lhs,const modular &rhs){return modular(lhs)-=rhs;}
    friend modular operator*(const modular &lhs,const modular &rhs){return modular(lhs)*=rhs;}
    friend modular operator/(const modular &lhs,const modular &rhs){return modular(lhs)/=rhs;}
    friend istream &operator>>(istream &is,modular &o){long long x; is >> x; o=modular(x); return is;}
    friend ostream &operator<<(ostream &os,modular o){return os << o.val;}
};
typedef modular mint;

struct combinatorics{
    vector<mint> fac,invfac;
    void init(int n){
        fac.resize(n+1);
        invfac.resize(n+1);
        fac[0]=1;
        for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
        invfac[n]=fac[n].inv();
        for(int i=n;i>=1;i--)invfac[i-1]=invfac[i]*i;
    }
    mint C(int n,int r){
        if(r<0||r>n)return 0;
        return fac[n]*invfac[n-r]*invfac[r];
    }
    mint inv(int n){
        return invfac[n]*fac[n-1];
    }
}comb;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    
}
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> p2;

const ll mod=1e9+7;

template<class T>
ll binpow(T a,ll b){T res=1;for(;b>0;b>>=1,a*=a)if(b&1)res*=a;return res;}

constexpr ll mul(ll a,ll b){ll res=(a*b-ll(1.l*a*b/mod)*mod)%mod;if(res<mod)res+=mod;return res;}

struct Modular{
    ll x;
    constexpr Modular(ll x=0):x(norm(x%mod)){}
    constexpr ll norm(ll x)const{if(x<0)x+=mod;if(x>=mod)x-=mod;return x;}
    explicit constexpr operator ll()const{return x;}
    constexpr Modular operator-()const{return Modular(-x);}
    constexpr Modular inv()const{return binpow(*this,mod-2);}
    constexpr Modular& operator+=(const Modular &rhs){x=norm(x+rhs.x);return *this;}
    constexpr Modular& operator-=(const Modular &rhs){x=norm(x-rhs.x);return *this;}
    constexpr Modular& operator*=(const Modular &rhs){x=mul(x,rhs.x);return *this;}
    constexpr Modular& operator/=(const Modular &rhs){return *this*=rhs.inv();}
    friend constexpr Modular operator+(const Modular &lhs,const Modular &rhs){return Modular(lhs)+=rhs;}
    friend constexpr Modular operator-(const Modular &lhs,const Modular &rhs){return Modular(lhs)-=rhs;}
    friend constexpr Modular operator*(const Modular &lhs,const Modular &rhs){return Modular(lhs)*=rhs;}
    friend constexpr Modular operator/(const Modular &lhs,const Modular &rhs){return Modular(lhs)/=rhs;}
    friend constexpr istream& operator>>(istream &is,Modular &o){ll x{};is>>x;o=Modular(x);return is;}
    friend constexpr ostream& operator<<(ostream &os,const Modular &o){return os<<o.x;}
    friend constexpr bool operator==(const Modular &lhs,const Modular &rhs){return lhs.x==rhs.x;};
    friend constexpr bool operator!=(const Modular &lhs,const Modular &rhs){return lhs.x!=rhs.x;};
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    
}
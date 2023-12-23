#pragma once
#include "Header.hpp"
#include "NumberTheory/ModularArithmetic.hpp"
#include "NTT.hpp"

#define T mint
using poly = vector<T>;
poly rsz(const poly &p,int n){
    if(n<=sz(p))return poly(begin(p),begin(p)+n);
    poly q=p;q.resize(n);return q;
}
poly shift(poly p,int x) { 
	if (x>=0)p.insert(begin(p),x,0); 
	else assert(sz(p)+x>=0),p.erase(begin(p),begin(p)-x);
	return p; 
}
T eval(const poly &p,T x){
    T res=0;
    for(int i=sz(p)-1;i>=0;i--)res=res*x+p[i];
    return res;
}
poly deriv(const poly &p){
    poly res(max(0,sz(p)));
    for(int i=1;i<sz(p);i++)res[i-1]=T(i)*p[i];
    return res;
}
poly integ(const poly &p){
    poly res(sz(p)+1);
    for(int i=0;i<sz(p);i++)res[i+1]=p[i]*invmod(i+1);
    return res;
}
poly &operator+=(poly &lhs,const poly &rhs){
    lhs.resize(max(sz(lhs),sz(rhs)));
    for(int i=0;i<sz(rhs);i++)lhs[i]+=rhs[i];
    return lhs;
}
poly &operator-=(poly &lhs,const poly &rhs){
    lhs.resize(max(sz(lhs),sz(rhs)));
    for(int i=0;i<sz(rhs);i++)lhs[i]-=rhs[i];
    return lhs;
}
poly &operator*=(poly &lhs,const T &rhs){for(auto &x:lhs)x*=rhs;return lhs;}
poly &operator/=(poly &lhs,const T &rhs){for(auto &x:lhs)x/=rhs;return lhs;}
poly operator+(poly lhs,const poly &rhs){return lhs+=rhs;}
poly operator-(poly lhs,const poly &rhs){return lhs-=rhs;}
poly operator*(poly lhs,const T &rhs){return lhs*=rhs;}
poly operator*(const T &lhs,poly rhs){return rhs*=lhs;}
poly operator/(poly lhs,const T &rhs){return lhs/=rhs;}
poly operator*(poly lhs,const poly &rhs){return ntt::conv(lhs,rhs);} // chang this if can't do ntt
poly &operator*=(poly &lhs,const poly &rhs){return lhs=lhs*rhs;}

poly inv(const poly &p,int n){
    assert(p[0]!=0);
    poly q{p[0].inv()};
    for(int i=2;i/2<n;i*=2)q=2*q-rsz(rsz(p,i)*rsz(q*q,i),i);
    return q;
}
poly sqrt(const poly &p,int n){
    assert(p[0]==1);
    poly q{1};
    for(int i=2;i/2<n;i*=2)q=invmod(2)*(q+rsz(rsz(p,i)*inv(q,i),i));
    return q;
}
poly log(const poly &p,int n){
    return integ(rsz(deriv(rsz(p,n+1))*inv(rsz(p,n-1),n-1),n-1));
}
poly exp(const poly &p,int n){
    poly q{1};
    for(int i=2;i/2<n;i*=2)q=q+rsz(q*(rsz(p,i)-log(q,i)),i);
    return q;
}
poly pow(const poly &p,int n,ll k){
    int l=0;
    while(l<n&&p[l]==0)l++;
    if(db(k*l)>=n)return poly(n,0);
    T a=p[l];
    poly t=a.inv()*shift(p,-l);
    return binpow(a,k)*rsz(shift(exp(k*log(t,n),n),k*l),n);
}
#undef T


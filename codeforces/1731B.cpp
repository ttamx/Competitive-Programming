#include<bits/stdc++.h>

using namespace std;

const long long mod=1e9+7;

template<long long mod>
struct modular{
  long long val;
  modular(long long x=0){ val=x%mod; if(val<0)val+=mod;}
  modular inv();
  modular& operator+=(const modular&o){val=(val+o.val)%mod; return *this;}
  modular& operator-=(const modular&o){val=(val-o.val+mod)%mod; return *this;}
  modular& operator*=(const modular&o){val=(val*o.val)%mod; return *this;}
  modular& operator/=(const modular&o){val=(val*o.inv().val)%mod; return *this;}
  friend modular operator+(const modular &lhs,const modular &rhs){return modular(lhs)+=rhs;}
  friend modular operator-(const modular &lhs,const modular &rhs){return modular(lhs)-=rhs;}
  friend modular operator*(const modular &lhs,const modular &rhs){return modular(lhs)*=rhs;}
  friend modular operator/(const modular &lhs,const modular &rhs){return modular(lhs)/=rhs;}
  modular& operator++(){return *this+=1;}
  modular& operator--(){return *this-=1;}
  modular operator++(int){modular ret=*this; *this+=1; return ret;}
  modular operator--(int){modular ret=*this; *this-=1; return ret;}
  bool operator==(const modular &o){return val==o.val;}
  bool operator!=(const modular &o){return val!=o.val;}
  modular binpow(long long pow)const{modular tmp=*this,ret=1; for(;pow;tmp*=tmp,pow>>=1)if(pow&1)ret*=tmp; return ret;}
  modular inv()const{return binpow(mod-2);}
};

typedef modular<mod> mint;

void runcase(){
    long long n;
    cin >> n;
    mint x(n);
    cout << (mint(2022)*((x*(x+mint(1))*(2*x+mint(1))/mint(3))-(x*(x+1)/mint(2)))).val << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();   
}
#include<bits/stdc++.h>

using namespace std;

//BINPOW
template<class T>
T binpow(T num,long long pow){
    T res=1;
    for(;pow;num*=num,pow>>=1)if(pow&1)res*=num;
    return res;
}
//--------------------------------------------------------
//MODULAR
long long mod=91308403229047;

struct modular{
    long long val;
    modular(long long x=0){ val=x%mod; if(val<0)val+=mod;}
    modular inv()const{return binpow(*this,mod-2);}
    modular& operator+=(const modular&o){val=(val+o.val)%mod; return *this;}
    modular& operator-=(const modular&o){val=(val-o.val+mod)%mod; return *this;}
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
    friend ostream &operator<<(ostream &os,modular &o){return os << o.val;}
};
typedef modular mint;
//--------------------------------------------------------

typedef long long ll;

const int N=2005;
const int A=30;

string a,b;
mint pw[A],qa[N],qb[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    pw[0]=1;
    for(int i=1;i<A;i++)pw[i]=pw[i-1]*2003;
    cin >> a >> b;
    for(int i=0;i<a.size();i++)qa[i+1]=qa[i]+pw[a[i]-'A'];
    for(int i=0;i<b.size();i++)qb[i+1]=qb[i]+pw[b[i]-'A'];
    ll ans=0;
    for(int sz=min(a.size(),b.size());sz>=1;sz--){
        map<ll,bool> mp;
        for(int l=0,r=sz-1;r<a.size();l++,r++)mp[(qa[r+1]-qa[l]).val]=true;
        for(int l=0,r=sz-1;r<b.size();l++,r++)if(mp[(qb[r+1]-qb[l]).val])cout << sz,exit(0);
    }
    cout << 0;
}
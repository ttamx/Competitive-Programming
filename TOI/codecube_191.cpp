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
long long mod=16550260501183;

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

const int N=2005;

string a,b;
mint hsh[N],ha[N],hb[N];

mt19937_64 rng(time(0));

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> a >> b;
    for(int i=0;i<256;i++)hsh[i]=rng();
    for(int i=1;i<=a.size();i++)ha[i]=ha[i-1]+hsh[a[i-1]];
    for(int i=1;i<=b.size();i++)hb[i]=hb[i-1]+hsh[b[i-1]];
    for(int sz=min(a.size(),b.size());sz>0;sz--){
        map<int,bool> mp;
        bool ok=false;
        for(int i=sz;i<=a.size();i++)mp[(ha[i]-ha[i-sz]).val]=true;
        for(int i=sz;i<=b.size();i++)if(mp[(hb[i]-hb[i-sz]).val])ok=true;
        if(ok){
            cout << sz;
            return 0;
        }
    }
    cout << 0;
}
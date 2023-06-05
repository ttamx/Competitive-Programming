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
long long mod=998244353;

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
    friend ostream &operator<<(ostream &os,modular o){return os << o.val;}
};
typedef modular mint;
//--------------------------------------------------------
//COMBINTORICS
vector<mint> fac,invfac;

void prefac(int n){
    fac.resize(n+1);
    invfac.resize(n+1);
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    invfac[n]=fac[n].inv();
    for(int i=n;i>=1;i--)invfac[i-1]=invfac[i]*i;
}

mint C(int n,int r){
    return fac[n]*invfac[n-r]*invfac[r];
}
//--------------------------------------------------------

mt19937_64 rng(time(nullptr));

void runcase(){
    int n,k;
    cin >> n >> k;
    prefac(2*n);
    vector<unsigned long long> a(n+5);
    for(int i=0;i<k;i++){
        int l,r;
        cin >> l >> r;
        unsigned long long x=rng();
        a[l]^=x;
        a[r+1]^=x;
    }
    map<unsigned long long,int> mp;
    for(int i=1;i<=n;i++)a[i]^=a[i-1];
    for(int i=1;i<=n;i++)mp[a[i]]++;
    mint ans=1;
    for(auto [x,y]:mp){
        if(y&1)return void(cout << 0 << "\n");
        ans*=C(y,y/2)/(y/2+1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
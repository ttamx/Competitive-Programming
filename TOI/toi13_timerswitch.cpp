#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e6+5;

//BINPOW
template<class T>
T binpow(T num,long long pow){
    T res=1;
    for(;pow;num*=num,pow>>=1)if(pow&1)res*=num;
    return res;
}
//--------------------------------------------------------
//MODULAR
long long mod=1e9+7;

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
    friend bool operator==(const modular &lhs,const modular &rhs){return lhs.val==rhs.val;}
    friend bool operator!=(const modular &lhs,const modular &rhs){return lhs.val!=rhs.val;}
    friend modular operator+(const modular &lhs,const modular &rhs){return modular(lhs)+=rhs;}
    friend modular operator-(const modular &lhs,const modular &rhs){return modular(lhs)-=rhs;}
    friend modular operator*(const modular &lhs,const modular &rhs){return modular(lhs)*=rhs;}
    friend modular operator/(const modular &lhs,const modular &rhs){return modular(lhs)/=rhs;}
    friend istream &operator>>(istream &is,modular o){long long x; is >> x; o=modular(x); return is;}
    friend ostream &operator<<(ostream &os,modular o){return os << o.val;}
};
typedef modular mint;
//--------------------------------------------------------

int n;
string s;
mint hsh[N];
mint pw[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> s;
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2;
    for(int i=1;i<=n;i++)hsh[i]=hsh[i-1]+pw[i]*(s[i-1]-48);
    for(int i=1;i<=n;i++){
        if(n%i)continue;
        bool ok=true;
        for(int j=i;j<n;j+=i){
            if((hsh[j]-hsh[j-i])*pw[i]!=hsh[j+i]-hsh[j]){
                ok=false;
                break;
            }
        }
        if(ok){
            cout << i;
            return 0;
        }
    }
}
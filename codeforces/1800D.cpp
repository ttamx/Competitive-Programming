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
long long mod=980314633170013;

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

const int N=2e5+5;

mint pw[N];

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    vector<mint> hsh(n+1);
    for(int i=0;i<n;i++)hsh[i+1]=hsh[i]+(s[i]-'a'+1)*pw[i];
    set<long long> ss;
    for(int i=2;i<=n;i++){
        ss.insert((hsh[i-2]*pw[2]+hsh[n]-hsh[i]).val);
    }
    cout << ss.size() << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    pw[0]=1;
    for(int i=1;i<N;i++)pw[i]=pw[i-1]*29;
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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

const int N=(1<<19)+5;

int n;
int lg[N],a[N],freq[N];
mint ans=1;

void runcase(){
    cin >> n;
    prefac(1<<n);
    for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;
    freq[0]=freq[1]=1;
    for(int i=2;i<n;i++)freq[i]=freq[i-1]*2;
    for(int i=0;i<1<<n;i++){
        cin >> a[i];
        if(a[i]>0){
            freq[lg[a[i]-1]]--;
        }
    }
    for(int i=0;i<n;i++){
        int d=1<<i;
        int cnt=freq[n-i-1];
        for(int j=0;j<n;j+=2*d){
            if(a[j]!=-1&&lg[a[j]-1]==n-i-1){
                swap(a[j],a[j+d]);
            }
            if(a[j+d]!=-1&&lg[a[j+d]-1]!=n-i-1){
                swap(a[j],a[j+d]);
            }
            if(a[j+d]!=-1&&lg[a[j+d]-1]!=n-i-1){
                cout << 0;
                return;
            }
        }
        ans*=fac[freq[n-i-1]];
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
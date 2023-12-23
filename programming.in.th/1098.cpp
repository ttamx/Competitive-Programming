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

typedef tuple<int,int,int,int> t4;

const int N=505;

int n,k;
int a[N];
pair<int,int> mn[N][N];
map<t4,mint> mp;

mint sol(int l,int r,int h,int k){
    if(k==0)return 1;
    int sz=r-l+1;
    if(sz<k)return 0;
    if(l==r)return a[l]-h;
    t4 hsh(l,r,h,k);
    auto it=mp.find(hsh);
    if(it!=mp.end())return it->second;
    if(k==0)return mp[hsh]=1;
    int d=mn[l][r].first-h;
    if(d==0){
        mint res=0;
        for(int i=0;i<=k;i++)res+=sol(l,mn[l][r].second-1,h,i)*sol(mn[l][r].second+1,r,h,k-i);
        return mp[hsh]=res;
    }
    mint res=0;
    for(int i=0;i<=k;i++)if(i<=d&&i<=sz-k+i)res+=C(d,i)*C(sz-k+i,i)*fac[i]*sol(l,r,h+d,k-i);
    return mp[hsh]=res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    prefac(1e6);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)mn[i][i]={a[i],i};
    for(int sz=2;sz<=n;sz++)for(int l=1,r=sz;r<=n;l++,r++)mn[l][r]=min(mn[l][r-1],mn[l+1][r]);
    cout << sol(1,n,0,k);
}
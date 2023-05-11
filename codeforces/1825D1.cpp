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

void prefac(long long n){
    fac.resize(n+1);
    invfac.resize(n+1);
    fac[0]=1;
    for(long long i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    invfac[n]=fac[n].inv();
    for(long long i=n;i>=1;i--)invfac[i-1]=invfac[i]*i;
}

mint C(long long n,long long r){
    if(r<0||r>n)return 0;
    return fac[n]*invfac[n-r]*invfac[r];
}
//--------------------------------------------------------

const long long N=2e5+5;

long long n,k;
vector<long long> adj[N];
long long sz[N];
mint ans;

void dfs(int u,int p){
    sz[u]=1;
    ans+=C(n-1,k-1);
    ans+=C(n-1,k);
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        sz[u]+=sz[v];
        ans-=C(sz[v],k);
    }
    int sum=n-sz[u];
    ans-=C(sum,k);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    if(k==1||k==3){
        cout << 1;
        return 0;
    }
    prefac(n);
    for(long long i=1;i<n;i++){
        long long u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,-1);
    ans/=C(n,k);
    cout << ans;
}
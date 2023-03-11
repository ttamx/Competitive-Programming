#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

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
    friend ostream &operator<<(ostream &os,modular &o){return os << o.val;}
};
typedef modular mint;
//--------------------------------------------------------
//COMBINTORICS
vector<mint> fac,invfac;

void prefac(int n){
    fac.resize(n+1);
    invfac.resize(n+1);
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    invfac[n]=fac[n].inv();
    for(int i=n;i>=1;i--)invfac[i-1]=invfac[i]*i;
}

mint C(int n,int r){
    return fac[n]*invfac[n-r]*invfac[r];
}
//--------------------------------------------------------

const int N=2e5+5;

mint pw[N];

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n+1);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> lv(n+1);
    mint ans=0;
    function<void(int,int)> dfs=[&](int u,int p){
        lv[u]=1;
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            lv[u]=max(lv[u],lv[v]+1);
        }
        ans+=pw[n-1]*lv[u];
    };
    dfs(1,0);
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    pw[0]=1;
    for(int i=1;i<N;i++)pw[i]=pw[i-1]*2;
    int t(1);
    cin >> t;
    while(t--)runcase();
}
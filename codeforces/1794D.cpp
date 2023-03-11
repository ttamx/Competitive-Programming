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
    if(r>n)return 0;
    return fac[n]*invfac[n-r]*invfac[r];
}
//--------------------------------------------------------

typedef long long ll;

const int N=1e6+5;
const int M=4060;

bool notprime[N];
int cnt[N];
mint dp[M][M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    notprime[0]=notprime[1]=true;
    for(int i=2;i<N;i++){
        if(notprime[i])continue;
        for(int j=i+i;j<N;j+=i)notprime[j]=true;
    }
    int n;
    cin >> n;
    prefac(2*n);
    vector<int> a(2*n);
    vector<int> p,np;
    p.emplace_back(0);
    np.emplace_back(0);
    for(auto &x:a){
        cin >> x;
        cnt[x]++;
        if(notprime[x])np.emplace_back(x);
        else p.emplace_back(x);
    }
    sort(p.begin(),p.end());
    sort(np.begin(),np.end());
    p.erase(unique(p.begin(),p.end()),p.end());
    np.erase(unique(np.begin(),np.end()),np.end());
    dp[0][0]=fac[n];
    for(int i=1;i<np.size();i++)dp[0][0]*=invfac[cnt[np[i]]];
    for(int i=1;i<p.size();i++)for(int j=0;j<=n;j++)dp[i][j]=dp[i-1][j]*invfac[cnt[p[i]]]+(j>0?dp[i-1][j-1]*invfac[cnt[p[i]]-1]:0);
    cout << dp[p.size()-1][n];
}
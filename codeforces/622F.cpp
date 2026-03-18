#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

mint lagrange_interpolate(vector<mint> &f,mint c){
    int n=f.size();
    if(c.val()<n)return f[c.val()];
    vector<mint> l(n+1),r(n+1);
    l[0]=r[n]=1;
    for(int i=0;i<n;i++)l[i+1]=l[i]*(c-i);
    for(int i=n-1;i>=0;i--)r[i]=r[i+1]*(c-i);
    mint ans=0;
    for(int i=0;i<n;i++){
        mint cur=f[i]*comb.ifac(i)*comb.ifac(n-i-1);
        if((n-i-1)&1)cur*=-1;
        ans+=cur*l[i]*r[i+1];
    }
    return ans;
}

mint binpow(mint a,int b){
    mint res=1;
    while(b>0){
        if(b&1)res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    mint x;
    int n;
    cin >> x >> n;
    vector<mint> f(n+2);
    for(int i=1;i<=n+1;i++){
        f[i]=f[i-1]+binpow(i,n);
    }
    cout << lagrange_interpolate(f,x) << "\n";
}
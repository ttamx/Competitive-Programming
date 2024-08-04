#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

mint pow(mint a,ll n){
    mint res=1;
    while(n>0){
        if(n&1)res*=a;
        a*=a;
        n>>=1;
    }
    return res;
}

void runcase(){
    int n,m,k,x,y;
    cin >> n >> m >> k >> x >> y;
    k=min(k,n);
    mint p=mint(x)/y;
    mint q=1-p;
    vector<mint> fac(n+1),ifac(n+1);
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    ifac[n]=fac[n].inv();
    for(int i=n;i>=1;i--)ifac[i-1]=ifac[i]*i;
    auto C=[&](int n,int r){
        return fac[n]*ifac[r]*ifac[n-r];
    };
    mint ans=0;
    for(int i=1;i<=k;i++){
        mint res=pow((pow(p+q,i)+pow(q-p,i))/2,m);
        ans+=res*C(n,i);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
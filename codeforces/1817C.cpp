#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n;
    cin >> n;
    vector<mint> a(n+1),b(n+1);
    vector<mint> fac(n+1),ifac(n+1);
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    ifac[n]=fac[n].inv();
    for(int i=n;i>=1;i--)ifac[i-1]=ifac[i]*i;
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    mint k=0,f=0,g=0;
    for(int i=0;i<=n;i++){
        mint v=ifac[i]*ifac[n-i];
        k+=a[i]*(i%2==0?v:-v);
    }
    mint tot=mint(1LL*n*(n-1)/2);
    for(int i=0;i<=n;i++){
        mint v=ifac[i]*ifac[n-i]*(tot-i);
        f+=a[i]*(i%2==0?v:-v);
    }
    for(int i=0;i<=n;i++){
        mint v=ifac[i]*ifac[n-i]*(tot-i);
        g+=b[i]*(i%2==0?v:-v);
    }
    cout << (f-g)/(k*n) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
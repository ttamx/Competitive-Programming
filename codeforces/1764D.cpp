#include "template.hpp"
#include "modular-arithmetic/modint.hpp"

using mint = ModInt<0>;

void runcase(){
    int n,mod;
    cin >> n >> mod;
    mint::set_mod(mod);
    vector<mint> fac(n+1);
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    vector C(n+1,vector<mint>(n+1));
    for(int i=0;i<=n;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
    mint ans=0;
    int m=n/2;
    for(int i=m;i<=n-2;i++){
        for(int j=0;j<=n-i-2;j++){
            ans+=C[n-i-2][j]*fac[i+j-1]*(2*m-i);
        }
    }
    if(n%2==0)ans+=fac[n-2];
    cout << ans*n << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
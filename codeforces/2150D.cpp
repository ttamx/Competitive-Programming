#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<mint> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<mint> f(n+1),g(n+1);
    for(int i=0;i<n;i++){
        f[i+1]=f[i]+a[i];
        g[i+1]=g[i]+f[i+1];
    }
    mint ans=0;
    for(auto x:a){
        ans+=x*n;
    }
    for(int x=0;x<2;x++){
        for(int y=0;y<2;y++){
            for(int i=2;i<=n;i++){
                int s=n-x-y-i;
                if(s<0)break;
                if(s%2==1)continue;
                s/=2;
                mint sum=g[n]-g[n-i]-g[i-1];
                mint avg=s*comb.inv(i)*2+1;
                mint ways=comb.H(s,i);
                ans+=ways*sum*avg;
                if(x){
                    ans+=ways*f[n-i+1];
                }
                if(y){
                    ans+=ways*(f[n]-f[i-1]);
                }
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

const int N=1e6+5;

int lp[N];
mint pw[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(!lp[i]){
            for(int j=i;j<N;j+=i){
                if(!lp[j]){
                    lp[j]=i;
                }
            }
        }
    }
    pw[0]=1;
    for(int i=1;i<N;i++){
        pw[i]=pw[i-1]*2;
    }
    int t;
    cin >> t;
    while(t--){
        int n,v;
        cin >> v >> n;
        mint ans=1;
        while(v>1){
            int p=lp[v];
            int c=0;
            while(v%p==0){
                v/=p;
                c++;
            }
            ans*=comb.C(n+c-1,c);
        }
        cout << ans*pw[n-1] << "\n";
    }
}
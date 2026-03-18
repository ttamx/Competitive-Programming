#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

mint binpow(mint a,ll b){
    mint res=1;
    while(b>0){
        if(b&1)res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}

void runcase(){
    int n;
    cin >> n;
    if(n%2==0){
        n/=2;
        cout << mint(2)*(binpow(mint(2),2*n-3)+3*binpow(mint(2),n-2)-1) << "\n";
    }else{
        cout << 0 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
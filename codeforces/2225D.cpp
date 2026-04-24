#include "template.hpp"
#include "modular-arithmetic/modint.hpp"

using mint = mint998;

mint f0(ll n){
    return mint((n+1)/4)+1;
}

mint f1(ll n){
    return mint((n+3)/4);
}

void runcase(){
    ll n,x;
    cin >> n >> x;
    x--;
    mint ans=0;
    ans+=f0(x)*(f0(n)-f0(x));
    ans+=f1(x)*(f1(n)-f1(x));
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
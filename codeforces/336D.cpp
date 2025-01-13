#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

void runcase(){
    int n,m,g;
    cin >> n >> m >> g;
    if(m==0){
        cout << ((n-1)%2==g) << "\n";
        return;
    }
    mint ans=0;
    for(int i=0;i<n+m-1&&i<=n;i+=2){
        ans+=comb.C(n+m-i-1,m-1);
    }
    if(m==1&&(n+m)%2==0){
        ans++;
    }
    if(g){
        ans=comb.C(n+m,n)-ans;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
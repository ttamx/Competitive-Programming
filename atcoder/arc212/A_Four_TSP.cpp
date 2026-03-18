#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    mint ans=0;
    for(int i=2;i+4<=n;i++){
        for(int j=2;j+i+2<=n;j++){
            int k=n-i-j;
            ans+=mint(i+j+k-max({i,j,k}))*mint(i-1)*mint(j-1)*mint(k-1);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
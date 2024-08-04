#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<mint> a(n);
    for(auto &x:a)cin >> x;
    mint sum1=0,sum2=0;
    for(int i=0;i<k;i++)sum1+=a[i];
    for(int i=k;i<n;i++)sum2+=a[i];
    mint ans=mint(k)/mint(n-k+1)*mint((n-k)/2+1)*sum1/mint(k)+mint((n-k+1)/2)*sum2/mint(n-k);
    cout << ans << " " << sum1+sum2-ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
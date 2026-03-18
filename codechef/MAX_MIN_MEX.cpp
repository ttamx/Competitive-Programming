#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    int mx=0,cnt=0;
    for(int i=0;i<n;i++){
        int j=i;
        while(j+1<n&&a[j+1]==a[j]+1)j++;
        int sz=j-i+1;
        if(sz>mx)mx=sz,cnt=0;
        if(sz==mx)cnt++;
        i=j;
    }
    mint ans=cnt*comb.fac(n-mx);
    for(int i=0;i<mx-1;i++)ans*=2;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
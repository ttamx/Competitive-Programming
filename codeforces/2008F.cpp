#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n;
    cin >> n;
    mint sum=0,ans=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        ans+=sum*x;
        sum+=x;
    }
    ans/=(1LL*n*(n-1)/2);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
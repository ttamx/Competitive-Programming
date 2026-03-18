#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    for(int i=0;i<n;i++){
        a[i]*=1LL*(i+1)*(n-i);
    }
    sort(a.begin(),a.end());
    sort(b.rbegin(),b.rend());
    mint ans=0;
    for(int i=0;i<n;i++){
        ans+=mint(a[i])*b[i];
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
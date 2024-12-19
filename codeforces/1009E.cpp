#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<mint> a(n);
    for(auto &x:a){
        cin >> x;
    }
    mint ans=0;
    vector<mint> pw(n);
    pw[0]=1;
    for(int i=1;i<n;i++){
        pw[i]=pw[i-1]*2;
    }
    for(int i=1;i<n;i++){
        a[i]+=a[i-1];
    }
    for(int i=0;i<n;i++){
        ans+=(n-i-1)*a[i]*pw[n-i-2];
    }
    for(int i=0;i<n;i++){
        ans+=pw[n-i-1]*a[i];
    }
    for(int i=0;i<n;i++){
        ans+=pw[i]*a[n-i-1];
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
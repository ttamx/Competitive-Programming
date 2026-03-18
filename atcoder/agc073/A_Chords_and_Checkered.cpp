#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int L,k,n;
    cin >> L >> k >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<mint> pw(n+1);
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=pw[i-1]*2;
    }
    mint ans=n*pw[n-1];
    if(n>=3){
        for(int i=0;i<n;i++){
            a.emplace_back(a[i]+L);
        }
        for(int l=0,r=0;l<n;l++){
            while(r+1<2*n&&a[r+1]<a[l]+k){
                r++;
            }
            ans+=max(r-l-1,0)*pw[n-3];
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
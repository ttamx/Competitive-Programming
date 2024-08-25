#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n,k;
    cin >> n >> k;
    int cnt[2]={};
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    vector<mint> fac(n+1),ifac(n+1);
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    ifac[n]=fac[n].inv();
    for(int i=n;i>=1;i--)ifac[i-1]=ifac[i]*i;
    auto C=[&](int n,int r){
        if(n<0||r<0||n<r)return mint(0);
        return fac[n]*ifac[n-r]*ifac[r];
    };
    mint ans=0;
    for(int i=(k+1)/2;i<=n;i++){
        ans+=C(cnt[1],i)*C(cnt[0],k-i);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
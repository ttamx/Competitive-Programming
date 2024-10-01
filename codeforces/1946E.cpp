#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n,ml,mr;
    cin >> n >> ml >> mr;
    vector<int> a(ml),b(mr);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    reverse(a.begin(),a.end());
    if(a[0]!=b[0]||a.back()!=1||b.back()!=n)return void(cout << "0\n");
    vector<mint> fac(n+1),ifac(n+1);
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    ifac[n]=fac[n].inv();
    for(int i=n;i>=1;i--)ifac[i-1]=ifac[i]*i;
    auto C=[&](int n,int r){
        assert(n>=0&&r>=0&&r<=n);
        return fac[n]*ifac[n-r]*ifac[r];
    };
    auto P=[&](int n,int r){
        assert(n>=0&&r>=0&&r<=n);
        return fac[n]*ifac[n-r];
    };
    mint ans=C(n-1,a[0]-1);
    for(int i=1;i<ml;i++){
        ans*=P(a[i-1]-2,a[i-1]-a[i]-1);
    }
    for(int i=1;i<mr;i++){
        ans*=P(n-b[i-1]-1,b[i]-b[i-1]-1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
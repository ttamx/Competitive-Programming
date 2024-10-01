#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    if(n==2){
        cout << 3 << "\n";
        return;
    }
    sort(a.begin(),a.end());
    if(a.back()-a[0]>1){
        cout << 0 << "\n";
        return;
    }
    if(a[0]==n-1){
        cout << 1 << "\n";
        return;
    }
    int single=a.back()>a[0]?count(a.begin(),a.end(),a[0]):0;
    int multiple=n-single;
    int uniq=a.back()-single;
    int remain=multiple-uniq*2;
    if(uniq<=0||remain<0){
        cout << 0 << "\n";
        return;
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
    cout << C(n,single)*C(n-single,uniq)*C(uniq+remain-1,uniq-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
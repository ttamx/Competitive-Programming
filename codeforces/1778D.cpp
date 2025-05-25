#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    string s,t;
    cin >> s >> t;
    int d=0;
    for(int i=0;i<n;i++){
        d+=(s[i]!=t[i]);
    }
    vector<mint> a(n+1),b(n+1),f(n+1);
    a[n]=b[n]=1;
    for(int i=n-1;i>=1;i--){
        mint c=1/(n-(n-i)*b[i+1]);
        a[i]=c*(n+(n-i)*a[i+1]);
        b[i]=c*i;
    }
    f[0]=0;
    for(int i=1;i<=n;i++){
        f[i]=a[i]+b[i]*f[i-1];
    }
    cout << f[d] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
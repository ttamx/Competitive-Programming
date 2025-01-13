#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<mint> a(n+1),c(20);
    c[0]=1;
    for(int i=1;i<20;i++){
        c[i]=c[i-1]*(k+i-1)/mint(i);
    }
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=i,d=1;(j+=j&-j)<=n;d++){
            a[j]-=a[i]*c[d];
        }
        cout << a[i] << " \n"[i==n];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
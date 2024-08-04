#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "convolution/and-convolution.hpp"
#include "convolution/or-convolution.hpp"
#include "convolution/xor-convolution.hpp"

using mint = mint107;

void runcase(){
    int n;
    cin >> n;
    int m=1<<17;
    vector<mint> a(m);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a[x]++;
    }
    vector<mint> f(m);
    f[0]=0,f[1]=1;
    for(int i=2;i<m;i++)f[i]=f[i-1]+f[i-2];
    auto b=or_convolution(a,a);
    auto c=xor_convolution(a,a);
    for(int i=0;i<m;i++){
        a[i]*=f[i];
        b[i]*=f[i];
        c[i]*=f[i];
    }
    auto d=and_convolution(b,c);
    auto e=and_convolution(a,d);
    mint ans=0;
    for(int i=1;i<m;i<<=1)ans+=e[i];
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

const int N=5e5+5;
const int X=1e5+5;

int n;
int a[N];
mint val[X],aux[X];
vector<int> factor[X];
int phi[X];
mint pw[N];
mint ans[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<X;i++){
        phi[i]+=i;
        factor[i].emplace_back(i);
        for(int j=i*2;j<X;j+=i){
            phi[j]-=phi[i];
            factor[j].emplace_back(i);
        }
    }
    cin >> n;
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=pw[i-1]*2;
    }
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n;i++){
        for(auto d:factor[a[i]]){
            ans[i]+=aux[d]*phi[d];
            aux[d]+=pw[i];
        }
        ans[i+1]=ans[i]*2;
    }
    for(int i=0;i<n;i++){
        cout << ans[i] << "\n";
    }
}
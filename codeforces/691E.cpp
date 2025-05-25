#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "linear-algebra/matrix.hpp"

using mint = mint107;
using Mat = Matrix<mint,100>;

void runcase(){
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    Mat base;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(__builtin_popcountll(a[i]^a[j])%3==0){
                base[i][j]=1;
            }
        }
    }
    Mat res=base.pow(k-1);
    mint ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            ans+=res[i][j];
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
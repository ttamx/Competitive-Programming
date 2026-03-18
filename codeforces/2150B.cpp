#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    mint ans=1;
    ll cnt=0;
    for(int i=0;i<n;i++){
        cnt+=a[i];
        if(i*2+1==n){
            if(cnt<1){
                cout << "0\n";
                return;
            }
            ans*=mint(cnt);
            cnt--;
        }else if((i+1)*2<=n){
            if(cnt<2){
                cout << "0\n";
                return;
            }
            ans*=mint(cnt)*mint(cnt-1);
            cnt-=2;
        }
    }
    if(cnt>0){
        cout << "0\n";
        return;
    }
    for(auto x:a){
        ans*=comb.ifac(x);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
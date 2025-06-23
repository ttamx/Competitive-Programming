#include "template.hpp"
#include "modular-arithmetic/modint.hpp"

using mint = ModInt<0>;

template<class T>
constexpr T binpow(T a,ll b){T res=1;for(;b>0;b>>=1,a*=a)if(b&1)res*=a;return res;}

ll n;
int k,mod;

vector<mint> mul(vector<mint> a,vector<mint> b){
    vector<mint> c(k);
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            c[(i+j)%k]+=a[i]*b[j];
        }
    }
    return c;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> mod;
    mint::set_mod(mod);
    mint ans=binpow(mint(k),n);
    for(int x=0;x<k;x++){
        vector<mint> a(k),b(k);
        for(int i=0;i<k;i++)if(i*2%k!=x)b[i]=1;
        a[0]=1;
        for(ll m=n;m>0;m>>=1){
            if(m&1)a=mul(a,b);
            b=mul(b,b);
        }
        ans-=a[x];
    }
    cout << ans << "\n";
}
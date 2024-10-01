#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

template<class T>
T binpow(T a,ll b){
    T res=1;
    for(;b>0;b>>=1){
        if(b&1)res*=a;
        a*=a;
    }
    return res;
}

namespace ntt{
    const mint g=3;
    void ntt(vector<mint> &a){
        int n=a.size(),L=31-__builtin_clz(n);
        vector<mint> rt(n);
        rt[1]=1;
        for(int k=2,s=2;k<n;k*=2,s++){
            mint z[]={1,binpow(g,MOD>>s)};
            for(int i=k;i<2*k;i++)rt[i]=rt[i/2]*z[i&1];
        }
        vi rev(n);
        for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
        for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
        for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
            mint z=rt[j+k]*a[i+j+k];
            a[i+j+k]=a[i+j]-z;
            a[i+j]+=z;
        }
    }
    vector<mint> conv(const vector<mint> &a,const vector<mint> &b){
        if(a.empty()||b.empty())return {};
        int s=a.size()+b.size()-1,n=1<<32-__builtin_clz(s);
        mint inv=mint(n).inv();
        vector<mint> in1(a),in2(b),out(n);
        in1.resize(n),in2.resize(n);
        ntt(in1),ntt(in2);
        for(int i=0;i<n;i++)out[-i&(n-1)]=in1[i]*in2[i]*inv;
        ntt(out);
        return vector<mint>(out.begin(),out.begin()+s);
    }
}

void runcase(){
    int n;
    cin >> n;
    int m=1<<n;
    vector<mint> dp{0,2};
    vector<mint> fac(m+1),ifac(m+1);
    fac[0]=1;
    for(int i=1;i<=m;i++)fac[i]=fac[i-1]*i;
    ifac[m]=fac[m].inv();
    for(int i=m;i>=1;i--)ifac[i-1]=ifac[i]*i;
    auto C=[&](int n,int r){
        return fac[n]*ifac[n-r]*ifac[r];
    };
    int cur=2;
    for(int i=1;i<n;i++){
        int s=1<<i;
        vector<mint> ndp(s*2);
        for(int j=0;j<s;j++){
            for(int k=1;k<=s;k++){
                ndp[j+k]+=C(k+j-1,j)*C(s-k+s-j-1,s-j-1)*dp[j];
            }
        }
        for(auto &x:ndp){
            x*=2*fac[s];
        }
        swap(dp,ndp);
    }
    for(auto x:dp){
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
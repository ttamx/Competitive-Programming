#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;

const ll mod=998244353;

ll modpow(ll a,ll b){
    ll res=1;
    for(;b>0;a=a*a%mod,b>>=1)if(b&1)res=res*a%mod;
    return res;
}

namespace fft{
    const ll g=3;
    void ntt(vl &a){
        int n=a.size(),L=31-__builtin_clz(n);
        vl rt(n);
        rt[1]=1;
        for(int k=2,s=2;k<n;k*=2,s++){
            ll z[]={1,modpow(g,mod>>s)};
            for(int i=k;i<2*k;i++)rt[i]=rt[i/2]*z[i&1]%mod;
        }
        vi rev(n);
        for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
        for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
        for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
            ll z=rt[j+k]*a[i+j+k]%mod;
            a[i+j+k]=(a[i+j]-z+mod)%mod;
            a[i+j]=(a[i+j]+z)%mod;
        }
    }
    vl conv(const vl &a,const vl &b){
        if(a.empty()||b.empty())return {};
        int s=a.size()+b.size()-1,n=1<<32-__builtin_clz(s);
        ll inv=modpow(n,mod-2);
        vl in1(a),in2(b),out(n);
        in1.resize(n),in2.resize(n);
        ntt(in1),ntt(in2);
        for(int i=0;i<n;i++)out[-i&(n-1)]=in1[i]*in2[i]%mod*inv%mod;
        ntt(out);
        return vl(out.begin(),out.begin()+s);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vl a(n),b(m);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    vl c=fft::conv(a,b);
    for(auto x:c)cout << x << " ";
}
// tested on https://judge.yosupo.jp/problem/convolution_mod_1000000007
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

const ld PI=acosl(-1);
const int mod=1e9+7;

void fft(vector<cd> &a){
    int n=a.size(),L=31-__builtin_clz(n);
    vector<cd> rt(n);
    rt[1]=1;
    for(int k=2;k<n;k*=2){
        cd z=polar(1.l,PI/k);
        for(int i=k;i<k*2;i++)rt[i]=i&1?rt[i/2]*z:rt[i/2];
    }
    vector<int> rev(n);
    for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
    for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
    for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
        cd z=rt[j+k]*a[i+j+k];
        a[i+j+k]=a[i+j]-z;
        a[i+j]+=z;
    }
}

template<int M=mod>
vector<ll> convMod(const vector<ll> &a,const vector<ll> &b){
    if(a.empty()||b.empty())return {};
    vector<ll> res(a.size()+b.size()-1);
    int L=32-__builtin_clz(res.size()),n=1<<L,cut=int(sqrt(M));
    vector<cd> in1(n),in2(n),out1(n),out2(n);
    for(int i=0;i<a.size();i++)in1[i]=cd(int(a[i])/cut,int(a[i])%cut); // a1 + i * a2
    for(int i=0;i<b.size();i++)in2[i]=cd(int(b[i])/cut,int(b[i])%cut); // b1 + i * b2
    fft(in1),fft(in2);
    for(int i=0;i<n;i++){
        int j=-i&(n-1);
        out1[j]=(in1[i]+conj(in1[j]))*in2[i]/(2.l*n); // f1 * (g1 + i * g2) = f1 * g1 + i f1 * g2
        out2[j]=(in1[i]-conj(in1[j]))*in2[i]/cd(0.l,2.l*n); // f2 * (g1 + i * g2) = f2 * g1 + i f2 * g2
    }
    fft(out1),fft(out2);
    for(int i=0;i<res.size();i++){
        ll x=round(real(out1[i])),y=round(imag(out1[i]))+round(real(out2[i])),z=round(imag(out2[i]));
        res[i]=((x%M*cut+y)%M*cut+z)%M;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<ll> a(n),b(m);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    auto c=convMod(a,b);
    for(auto x:c)cout << x << " ";
}
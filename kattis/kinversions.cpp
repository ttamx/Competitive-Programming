#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;

const ld PI=acosl(-1);

namespace fft{
    typedef complex<ld> cd;
    typedef vector<cd> vc;
    void fft(vc &a){
        int n=a.size(),L=31-__builtin_clz(n);
        vc rt(n);
        rt[1]=1;
        for(int k=2;k<n;k*=2){
            cd z=polar(1.l,PI/k);
            for(int i=k;i<2*k;i++)rt[i]=i&1?rt[i/2]*z:rt[i/2];
        }
        vi rev(n);
        for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
        for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
        for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
            cd z=rt[j+k]*a[i+j+k];
            a[i+j+k]=a[i+j]-z;
            a[i+j]+=z;
        }
    }
    vl conv(const vl &a,const vl &b){
        if(a.empty()||b.empty())return {};
        vl res(a.size()+b.size()-1);
        int n=1<<(32-__builtin_clz(res.size()));
        vc in(n),out(n);
        copy(a.begin(),a.end(),in.begin());
        for(int i=0;i<b.size();i++)in[i].imag(b[i]);
        fft(in);
        for(auto &x:in)x*=x;
        for(int i=0;i<n;i++)out[i]=(in[-i&(n-1)]-conj(in[i]));
        fft(out);
        for(int i=0;i<res.size();i++)res[i]=imag(out[i])/(4*n)+.5;
        return res;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    int n=s.size();
    vl pa(n),pb(n);
    for(int i=0;i<n;i++){
        if(s[i]=='A')pa[i]=1;
        else pb[n-i-1]=1;
    }
    vl pc=fft::conv(pa,pb);
    for(int i=1;i<n;i++)cout << pc[n+i-1] << "\n";
}